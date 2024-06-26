// Copyright 2017 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

// Original file path in: Source/Core/Common/UPnP.cpp. Modified a bit to differentiate EKA2L1 on the UPnP protocol

#include <common/upnp.h>
#include <common/log.h>

#include <array>
#include <cstdlib>
#include <cstring>
#include <miniupnpc.h>
#include <miniwget.h>
#include <string>
#include <thread>
#include <upnpcommands.h>
#include <upnperrors.h>
#include <vector>

static UPNPUrls s_urls;
static IGDdatas s_data;
static std::array<char, 20> s_our_ip;
static std::thread s_thread;

// called from ---UPnP--- thread
// discovers the IGD
static bool InitUPnP()
{
  static bool s_inited = false;
  static bool s_error = false;

  // Don't init if already inited
  if (s_inited)
    return true;

  // Don't init if it failed before
  if (s_error)
    return false;

  s_urls = {};
  s_data = {};

  // Find all UPnP devices
  int upnperror = 0;
  std::unique_ptr<UPNPDev, decltype(&freeUPNPDevlist)> devlist(nullptr, freeUPNPDevlist);
#if MINIUPNPC_API_VERSION >= 14
  devlist.reset(upnpDiscover(2000, nullptr, nullptr, 0, 0, 2, &upnperror));
#else
  devlist.reset(upnpDiscover(2000, nullptr, nullptr, 0, 0, &upnperror));
#endif
  if (!devlist)
  {
    if (upnperror == UPNPDISCOVER_SUCCESS)
    {
      LOG_WARN(eka2l1::COMMON, "No UPnP devices could be found.");
    }
    else
    {
      LOG_WARN(eka2l1::COMMON, "An error occurred trying to discover UPnP devices: {}",
                   strupnperror(upnperror));
    }

    s_error = true;

    return false;
  }

  // Look for the IGD
  bool found_valid_igd = false;
  for (UPNPDev* dev = devlist.get(); dev; dev = dev->pNext)
  {
    if (!std::strstr(dev->st, "InternetGatewayDevice"))
      continue;

    int desc_xml_size = 0;
    std::unique_ptr<char, decltype(&std::free)> desc_xml(nullptr, std::free);
    int statusCode = 200;
#if MINIUPNPC_API_VERSION >= 16
    desc_xml.reset(
        static_cast<char*>(miniwget_getaddr(dev->descURL, &desc_xml_size, s_our_ip.data(),
                                            static_cast<int>(s_our_ip.size()), 0, &statusCode)));
#else
    desc_xml.reset(static_cast<char*>(miniwget_getaddr(
        dev->descURL, &desc_xml_size, s_our_ip.data(), static_cast<int>(s_our_ip.size()), 0)));
#endif
    if (desc_xml && statusCode == 200)
    {
      parserootdesc(desc_xml.get(), desc_xml_size, &s_data);
      GetUPNPUrls(&s_urls, &s_data, dev->descURL, 0);

      found_valid_igd = true;
      //LOG_INFO(COMMON, "Got info from IGD at {}.", dev->descURL);
      break;
    }
    else
    {
      LOG_WARN(eka2l1::COMMON, "Error getting info from IGD at {}.", dev->descURL);
    }
  }

  if (!found_valid_igd)
    LOG_WARN(eka2l1::COMMON, "Could not find a valid IGD in the discovered UPnP devices.");

  s_inited = true;

  return true;
}

// called from ---UPnP--- thread
// Attempt to stop portforwarding.
// --
// NOTE: It is important that this happens! A few very crappy routers
// apparently do not delete UPnP mappings on their own, so if you leave them
// hanging, the NVRAM will fill with portmappings, and eventually all UPnP
// requests will fail silently, with the only recourse being a factory reset.
// --
static bool UnmapPort(const std::uint16_t port, const bool is_udp)
{
  std::string port_str = std::to_string(port);
  UPNP_DeletePortMapping(s_urls.controlURL, s_data.first.servicetype, port_str.c_str(), is_udp ? "UDP" : "TCP",
                         nullptr);

  return true;
}

// called from ---UPnP--- thread
// Attempt to portforward!
static bool MapPort(const char* addr, const bool is_udp, const std::uint16_t port)
{
  std::string port_str = std::to_string(port);
  int result = UPNP_AddPortMapping(
      s_urls.controlURL, s_data.first.servicetype, port_str.c_str(), port_str.c_str(), addr,
      (std::string("eka2l1-emu pf on ") + addr).c_str(), is_udp ? "UDP" : "TCP", nullptr, nullptr);

  if (result != 0)
    return false;

  return true;
}

// UPnP thread: try to map a port
static void MapPortThread(const std::uint16_t port, const bool is_udp)
{
  if (InitUPnP() && MapPort(s_our_ip.data(), is_udp, port))
  {
    LOG_INFO(eka2l1::COMMON, "Successfully mapped port {} to {}.", port, s_our_ip.data());
    return;
  }

  LOG_WARN(eka2l1::COMMON, "Failed to map port {} to {}.", port, s_our_ip.data());
}

// UPnP thread: try to unmap a port
static void UnmapPortThread(std::uint16_t port, bool is_udp)
{
   UnmapPort(port, is_udp);
}

void UPnP::TryPortmapping(std::uint16_t port, bool is_udp)
{
  if (s_thread.joinable())
    s_thread.join();
  s_thread = std::thread(&MapPortThread, port, is_udp);
}

void UPnP::StopPortmapping(std::uint16_t port, bool is_udp)
{
  if (s_thread.joinable())
    s_thread.join();
  s_thread = std::thread(&UnmapPortThread, port, is_udp);
  s_thread.join();
}