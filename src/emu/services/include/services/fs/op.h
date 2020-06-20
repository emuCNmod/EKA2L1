/*
 * Copyright (c) 2020 EKA2L1 Team.
 * 
 * This file is part of EKA2L1 project.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

namespace eka2l1::epoc {
    enum fs_message {
        fs_msg_add_filesystem = 0,
        fs_msg_remove_filesystem = 1,
        fs_msg_mount_filesystem = 2,
        fs_msg_notify_change = 3,
        fs_msg_notify_change_cancel = 4,
        fs_msg_drive_list = 5,
        fs_msg_drive = 6,
        fs_msg_volume = 7,
        fs_msg_set_volume = 8,
        fs_msg_subst = 9,
        fs_msg_set_subst = 10,
        fs_msg_real_name = 11,
        fs_msg_default_path = 12,
        fs_msg_set_default_path = 13,
        fs_msg_session_path = 14,
        fs_msg_set_session_path = 15,
        fs_msg_mkdir = 16,
        fs_msg_rmdir = 17,
        fs_msg_parse = 18,
        fs_msg_delete = 19,
        fs_msg_rename = 20,
        fs_msg_replace = 21,
        fs_msg_entry = 22,
        fs_msg_set_entry = 23,
        fs_msg_get_drive_name = 24,
        fs_msg_set_drive_name = 25,
        fs_msg_base_close = 26,         // EKA1
        fs_msg_format_subclose = 26,
        fs_msg_dir_subclose = 27,
        fs_msg_file_subclose = 28,
        fs_msg_raw_subclose = 29,
        fs_msg_file_open = 30,
        fs_msg_file_create = 31,
        fs_msg_file_replace = 32,
        fs_msg_file_temp = 33,
        fs_msg_file_read = 34,
        fs_msg_file_write = 35,
        fs_msg_file_lock = 36,
        fs_msg_file_unlock = 37,
        fs_msg_file_seek = 38,
        fs_msg_file_flush = 39,
        fs_msg_file_size = 40,
        fs_msg_file_set_size = 41,
        fs_msg_file_att = 42,
        fs_msg_file_set_att = 43,
        fs_msg_file_modified = 44,
        fs_msg_file_set_modified = 45,
        fs_msg_file_set = 46,
        fs_msg_file_changemode = 47,
        fs_msg_file_rename = 48,
        fs_msg_dir_open = 49,
        fs_msg_dir_read_one = 50,
        fs_msg_dir_read_packed = 51,
        fs_msg_format_open = 52,
        fs_msg_format_next = 53,
        fs_msg_raw_disk_open = 54,
        fs_msg_raw_disk_read = 55,
        fs_msg_raw_disk_write = 56,
        fs_msg_resouce_count_mark_start = 57,
        fs_msg_resouce_count_mark_end = 58,
        fs_msg_resource_count = 59,
        fs_msg_check_disk = 60,
        fs_msg_get_shortname = 61,
        fs_msg_get_longname = 62,
        fs_msg_is_file_open = 63,
        fs_msg_list_open_files = 64,
        fs_msg_get_notify_user = 65,
        fs_msg_set_notify_user = 66,
        fs_msg_is_file_in_rom = 67,
        fs_msg_is_valid_name = 68,
        fs_msg_debug_function = 69,
        fs_msg_read_file_section = 70,
        fs_msg_notify_change_ex = 71,
        fs_msg_notify_change_cancel_ex = 72,
        fs_msg_dismount_filesystem = 73,
        fs_msg_filesystem_name = 74,
        fs_msg_scan_drive = 75,
        fs_msg_control_io = 76,
        fs_msg_lock_drive = 77,
        fs_msg_unlock_drive = 78,
        fs_msg_clear_password = 79,
        fs_msg_notify_disk_space = 80,
        fs_msg_notify_disk_space_cancel = 81,
        fs_msg_file_drive = 82,
        fs_msg_remount_drive = 83,
        fs_msg_mount_filesystem_scan = 84,
        fs_msg_session_to_private = 85,
        fs_msg_private_path = 86,
        fs_msg_create_private_path = 87,
        fs_msg_add_ext = 88,
        fs_msg_mount_ext = 89,
        fs_msg_dismount_ext = 90,
        fs_msg_remove_ext = 91,
        fs_msg_ext_name = 92,
        fs_msg_startup_init_complete = 93,
        fs_msg_set_local_drive_mapping = 94,
        fs_msg_finalise_drive = 95,
        fs_msg_file_duplicate = 96,
        fs_msg_file_adopt = 97,
        fs_msg_swap_filesystem = 98,
        fs_msg_erase_password = 99,
        fs_msg_reserve_drive_space = 100,
        fs_msg_get_reserve_access = 101,
        fs_msg_release_reserve_access = 102,
        fs_msg_filename = 103,
        fs_msg_get_media_serial_number = 104,
        fs_msg_file_fullname = 105,
        fs_msg_add_plugin = 106,
        fs_msg_remove_plugin = 107,
        fs_msg_mount_plugin = 108,
        fs_msg_dismount_plugin = 109,
        fs_msg_plugin_name = 110,
        fs_msg_plugin_open = 111,
        fs_msg_plugin_subclose = 112,
        fs_msg_plugin_do_request = 113,
        fs_msg_plugin_do_control = 114,
        fs_msg_plugin_do_cancel = 115,
        fs_msg_notify_dismount = 116,
        fs_msg_notify_dismount_cancel = 117,
        fs_msg_allow_dismount = 118,
        fs_msg_set_startup_config = 119,
        fs_msg_file_read_cancel = 120,
        fs_msg_add_composite_mount = 121,
        fs_msg_set_session_flags = 122,
        fs_msg_set_system_drive = 123,
        fs_msg_block_map = 124,
        fs_msg_unclamp = 125,
        fs_msg_file_clamp = 126,
        fs_msg_query_volume_info_ext = 127,
        fs_msg_init_properties_file = 128,
        fs_msg_file_write_dirty = 129,
        fs_msg_sync_drive_thread = 130,
        fs_msg_add_proxy_drive = 131,
        fs_msg_remove_proxy_drive = 132,
        fs_msg_mount_proxy_drive = 133,
        fs_msg_dismount_proxy_drive = 134,
        fs_msg_notification_open = 135,
        fs_msg_notification_buffer = 136,
        fs_msg_notification_request = 137,
        fs_msg_notification_cancel = 138,
        fs_msg_notification_subclose = 139,
        fs_msg_notification_add = 140,
        fs_msg_notification_remove = 141,
        fs_msg_load_code_page = 142,
        fs_msg_max_client_operations
    };
}