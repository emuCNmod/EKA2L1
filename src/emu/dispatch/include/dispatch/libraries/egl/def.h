/*
 * Copyright (c) 2021 EKA2L1 Team.
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

#include <drivers/graphics/common.h>
#include <drivers/itc.h>

#include <dispatch/libraries/gles1/shaderman.h>

#include <common/vecx.h>
#include <common/container.h>

#include <kernel/common.h>

#include <cstdint>
#include <memory>
#include <map>
#include <stack>

namespace eka2l1 {
    namespace epoc {
        struct screen;
        struct canvas_base;
    }

    namespace drivers {
        class graphics_driver;
    }
}

namespace eka2l1::dispatch {
    enum {
        EGL_FALSE = 0,
        EGL_NO_SURFACE_EMU = 0,
        EGL_NO_CONTEXT_EMU = 0,
        EGL_TRUE = 1,
        EGL_PBUFFER_BIT_EMU = 1,
        EGL_PIXMAP_BIT_EMU = 2,
        EGL_WINDOW_BIT_EMU = 4,
        EGL_MAJOR_VERSION_EMU = 1,
        EGL_MINOR_VERSION_EMU = 4,
        EGL_BAD_ATTRIBUTE_EMU = 0x3004,
        EGL_BAD_CONFIG = 0x3005,
        EGL_BAD_CONTEXT_EMU = 0x3006,
        EGL_BAD_DISPLAY_EMU = 0x3008,
        EGL_BAD_NATIVE_WINDOW_EMU = 0x300B,
        EGL_BAD_PARAMETER_EMU = 0x300C,
        EGL_BAD_SURFACE_EMU = 0x300D,
        EGL_BUFFER_SIZE_EMU = 0x3020,
        EGL_ALPHA_SIZE_EMU = 0x3021,
        EGL_BLUE_SIZE_EMU = 0x3022,
        EGL_GREEN_SIZE_EMU = 0x3023,
        EGL_SURFACE_TYPE_EMU = 0x3033,
        EGL_RED_SIZE_EMU = 0x3024,
        EGL_HEIGHT_EMU = 0x3056,
        EGL_WIDTH_EMU = 0x3057,
        GL_NO_ERROR = 0,
        GL_ZERO_EMU = 0,
        GL_ONE_EMU = 1,
        GL_POINTS_EMU = 0x0000,
        GL_LINES_EMU = 0x0001,
        GL_LINE_LOOP_EMU = 0x0002,
        GL_LINE_STRIP_EMU = 0x0003,
        GL_TRIANGLES_EMU = 0x0004,
        GL_TRIANGLE_STRIP_EMU = 0x0005,
        GL_TRIANGLE_FAN_EMU = 0x0006,
        GL_NEVER_EMU = 0x0200,
        GL_LESS_EMU = 0x0201,
        GL_EQUAL_EMU = 0x0202,
        GL_LEQUAL_EMU = 0x0203,
        GL_GREATER_EMU = 0x0204,
        GL_NOTEQUAL_EMU = 0x0205,
        GL_GEQUAL_EMU = 0x0206,
        GL_ALWAYS_EMU = 0x0207,
        GL_FRONT_EMU = 0x0404,
        GL_BACK_EMU = 0x0405,
        GL_FRONT_AND_BACK_EMU = 0x0408,
        GL_INVALID_ENUM = 0x0500,
        GL_INVALID_VALUE = 0x0501,
        GL_INVALID_OPERATION = 0x0502,
        GL_STACK_OVERFLOW = 0x0503,
        GL_STACK_UNDERFLOW = 0x0504,
        GL_CLOCKWISE_EMU = 0x0900,
        GL_COUNTER_CLOCKWISE_EMU = 0x0901,
        GL_INVALID_FRAMEBUFFER_OPERATION = 0x0506,
        GL_EXP_EMU = 0x800,
        GL_EXP2_EMU = 0x801,
        GL_POINT_SMOOTH_EMU = 0x0B10,
        GL_LINE_SMOOTH_EMU = 0x0B20,
        GL_CULL_FACE_EMU = 0x0B44,
        GL_LIGHTING_EMU = 0x0B50,
        GL_COLOR_MATERIAL_EMU = 0x0B57,
        GL_FOG_EMU = 0x0B60,
        GL_FOG_DENSITY_EMU = 0x0B62,
        GL_FOG_START_EMU = 0x0B63,
        GL_FOG_END_EMU = 0x0B64,
        GL_FOG_MODE_EMU = 0x0B65,
        GL_FOG_COLOR_EMU = 0x0B66,
        GL_DEPTH_TEST_EMU = 0x0B71,
        GL_STENCIL_TEST_EMU = 0x0B90,
        GL_NORMALIZE_EMU = 0x0BA1,
        GL_ALPHA_TEST_EMU = 0x0BC0,
        GL_RESCALE_NORMAL_EMU = 0x803A,
        GL_POLYGON_OFFSET_FILL_EMU = 0x8037,
        GL_MULTISAMPLE_EMU = 0x809D,
        GL_SAMPLE_ALPHA_TO_COVERAGE_EMU = 0x809E,
        GL_SAMPLE_ALPHA_TO_ONE_EMU = 0x809F,
        GL_SAMPLE_COVERAGE_EMU = 0x80A0,
        GL_DITHER_EMU = 0x0BD0,
        GL_BLEND_EMU = 0x0BE2,
        GL_COLOR_LOGIC_OP_EMU = 0x0BF2,
        GL_LIGHT_MODEL_AMBIENT_EMU = 0x0B53,
        GL_LIGHT_MODEL_TWO_SIDE_EMU = 0x0B52,
        GL_SCISSOR_TEST_EMU = 0x0C11,
        GL_TEXTURE_2D_EMU = 0x0DE1,
        GL_DEPTH_BUFFER_BIT_EMU = 0x00000100,
        GL_STENCIL_BUFFER_BIT_EMU = 0x00000400,
        GL_COLOR_BUFFER_BIT_EMU = 0x00004000,
        GL_AMBIENT_EMU = 0x1200,
        GL_DIFFUSE_EMU = 0x1201,
        GL_SPECULAR_EMU = 0x1202,
        GL_POSITION_EMU = 0x1203,
        GL_SPOT_DIRECTION_EMU = 0x1204,
        GL_SPOT_EXPONENT_EMU = 0x1205,
        GL_SPOT_CUTOFF_EMU = 0x1206,
        GL_CONSTANT_ATTENUATION_EMU = 0x1207,
        GL_LINEAR_ATTENUATION_EMU = 0x1208,
        GL_QUADRATIC_ATTENUATION_EMU = 0x1209,
        GL_UNSIGNED_BYTE_EMU = 0x1401,
        GL_EMISSION_EMU = 0x1600,
        GL_SHININESS_EMU = 0x1601,
        GL_AMBIENT_AND_DIFFUSE_EMU = 0x1602,
        GL_MODELVIEW_EMU = 0x1700,
        GL_PROJECTION_EMU = 0x1701,
        GL_TEXTURE_EMU = 0x1702,
        GL_ALPHA_EMU = 0x1906,
        GL_RGB_EMU = 0x1907,
        GL_RGBA_EMU = 0x1908,
        GL_LUMINANCE_EMU = 0x1909,
        GL_LUMINANCE_ALPHA_EMU = 0x190A,
        GL_FLAT_EMU = 0x1D00,
        GL_SMOOTH_EMU = 0x1D01,
        GL_NEAREST_EMU = 0x2600,
        GL_LINEAR_EMU = 0x2601,
        GL_SRC_COLOR_EMU = 0x0300,
        GL_ONE_MINUS_SRC_COLOR_EMU = 0x0301,
        GL_SRC_ALPHA_EMU = 0x0302,
        GL_ONE_MINUS_SRC_ALPHA_EMU = 0x0303,
        GL_DST_ALPHA_EMU = 0x0304,
        GL_ONE_MINUS_DST_ALPHA_EMU = 0x305,
        GL_DST_COLOR = 0x0306,
        GL_ONE_MINUS_DST_COLOR = 0x0307,
        GL_SRC_ALPHA_SATURATE_EMU = 0x308,
        GL_MODULATE_EMU = 0x2100,
        GL_DECAL_EMU = 0x2101,
        GL_ADD_EMU = 0x0104,
        GL_REPLACE_EMU = 0x1E01,
        GL_TEX_ENV_MODE_EMU = 0x2200,
        GL_TEX_ENV_COLOR_EMU = 0x2201,
        GL_TEX_ENV_EMU = 0x2300,
        GL_NEAREST_MIPMAP_NEAREST_EMU = 0x2700,
        GL_LINEAR_MIPMAP_NEAREST_EMU = 0x2701,
        GL_NEAREST_MIPMAP_LINEAR_EMU = 0x2702,
        GL_LINEAR_MIPMAP_LINEAR_EMU = 0x2703,
        GL_LIGHT0_EMU = 0x4000,
        GL_LIGHT1_EMU = 0x4001,
        GL_LIGHT2_EMU = 0x4002,
        GL_LIGHT3_EMU = 0x4003,
        GL_LIGHT4_EMU = 0x4004,
        GL_LIGHT5_EMU = 0x4005,
        GL_LIGHT6_EMU = 0x4006,
        GL_LIGHT7_EMU = 0x4007,
        GL_UNSIGNED_SHORT_4_4_4_4_EMU = 0x8033,
        GL_UNSIGNED_SHORT_5_5_5_1_EMU = 0x8034,
        GL_UNSIGNED_SHORT_5_6_5_EMU = 0x8363,
        GL_VERTEX_ARRAY_EMU = 0x8074,
        GL_NORMAL_ARRAY_EMU = 0x8075,
        GL_COLOR_ARRAY_EMU = 0x8076,
        GL_TEXTURE_COORD_ARRAY_EMU = 0x8078,
        GL_VERTEX_ARRAY_POINTER_EMU = 0x808E,
        GL_NORMAL_ARRAY_POINTER_EMU = 0x808F,
        GL_COLOR_ARRAY_POINTER_EMU = 0x8090,
        GL_TEXTURE_COORD_ARRAY_POINTER_EMU = 0x8092,
        GL_TEXTURE0_EMU = 0x84C0,
        GL_TEXTURE1_EMU = 0x84C1,
        GL_TEXTURE2_EMU = 0x84C2,
        GL_ARRAY_BUFFER_EMU = 0x8892,
        GL_ELEMENT_ARRAY_BUFFER_EMU = 0x8893,
        GL_STATIC_DRAW_EMU = 0x88E4,
        GL_DYNAMIC_DRAW_EMU = 0x88E8,
        GL_SUBTRACT_EMU = 0x84E7,
        GL_COMBINE_EMU = 0x8570,
        GL_COMBINE_RGB_EMU = 0x8571,
        GL_COMBINE_ALPHA_EMU = 0x8572,
        GL_RGB_SCALE_EMU = 0x8573,
        GL_ADD_SIGNED_EMU = 0x8574,
        GL_INTERPOLATE_EMU = 0x8575,
        GL_CONSTANT_EMU = 0x8576,
        GL_PRIMARY_COLOR_EMU = 0x8577,
        GL_PREVIOUS_EMU = 0x8578,
        GL_OPERAND0_RGB_EMU = 0x8590,
        GL_OPERAND1_RGB_EMU = 0x8591,
        GL_OPERAND2_RGB_EMU = 0x8592,
        GL_OPERAND0_ALPHA_EMU = 0x8598,
        GL_OPERAND1_ALPHA_EMU = 0x8599,
        GL_OPERAND2_ALPHA_EMU = 0x859A,
        GL_ALPHA_SCALE_EMU = 0x0D1C,
        GL_SRC0_RGB_EMU = 0x8580,
        GL_SRC1_RGB_EMU = 0x8581,
        GL_SRC2_RGB_EMU = 0x8582,
        GL_SRC0_ALPHA_EMU = 0x8588,
        GL_SRC1_ALPHA_EMU = 0x8589,
        GL_SRC2_ALPHA_EMU = 0x858A,
        GL_DOT3_RGB_EMU = 0x86AE,
        GL_DOT3_RGBA_EMU = 0x86AF,
        GL_CLIP_PLANE0_EMU = 0x3000,
        GL_CLIP_PLANE1_EMU = 0x3001,
        GL_CLIP_PLANE2_EMU = 0x3002,
        GL_CLIP_PLANE3_EMU = 0x3003,
        GL_CLIP_PLANE4_EMU = 0x3004,
        GL_CLIP_PLANE5_EMU = 0x3005,
        GL_TEXTURE_MAG_FILTER_EMU = 0x2800,
        GL_TEXTURE_MIN_FILTER_EMU = 0x2801,
        GL_TEXTURE_WRAP_S_EMU = 0x2802,
        GL_TEXTURE_WRAP_T_EMU = 0x2803,
        GL_GENERATE_MIPMAP_EMU = 0x8191,
        GL_REPEAT_EMU = 0x2901,
        GL_CLAMP_TO_EDGE_EMU = 0x812F,
        GL_BYTE_EMU = 0x1400,
        GL_SHORT_EMU = 0x1402,
        GL_UNSIGNED_SHORT_EMU = 0x1403,
        GL_FLOAT_EMU = 0x1406,
        GL_FIXED_EMU = 0x140C,
        GL_MAXIMUM_MODELVIEW_MATRIX_STACK_SIZE = 16,
        GL_MAXIMUM_PROJECTION_MATRIX_STACK_SIZE = 2,
        GL_MAXIMUM_TEXTURE_MATRIX_STACK_SIZE = 2
    };

    using egl_display = std::uint32_t;
    using egl_boolean = std::uint32_t;

    struct egl_config {
        enum surface_type {
            EGL_SURFACE_TYPE_WINDOW = 0,
            EGL_SURFACE_TYPE_PBUFFER = 1
        };

        enum target_context_version {
            EGL_TARGET_CONTEXT_ES11 = 0,
            EGL_TARGET_CONTEXT_ES2 = 1
        };

        std::uint32_t config_;

        explicit egl_config(const std::uint32_t config)
            : config_(config) {
        }

        void set_buffer_size(const std::uint8_t buffer_size);
        std::uint8_t buffer_size() const;

        void set_surface_type(const surface_type type);
        surface_type get_surface_type() const;

        target_context_version get_target_context_version();
        void set_target_context_version(const target_context_version ver);
    };

    enum egl_context_type {
        EGL_GLES1_CONTEXT,
        EGL_GLES2_CONTEXT
    };

    struct egl_context;

    struct egl_surface {
        drivers::handle handle_;
        egl_config::surface_type surface_type_;

        epoc::screen *backed_screen_;
        epoc::canvas_base *backed_window_;

        eka2l1::vec2 dimension_;
        kernel::uid associated_thread_uid_;
        bool dead_pending_;

        egl_context *bounded_context_;

        explicit egl_surface(epoc::canvas_base *backed_window, epoc::screen *screen, eka2l1::vec2 dim,
            drivers::handle h, egl_config::surface_type surface_type);
    };

    struct egl_context {
        std::unique_ptr<drivers::graphics_command_list> command_list_;
        std::unique_ptr<drivers::graphics_command_list_builder> command_builder_;

        egl_surface *read_surface_;
        egl_surface *draw_surface_;

        kernel::uid associated_thread_uid_;
        bool dead_pending_;

        explicit egl_context();

        virtual void free(drivers::graphics_driver *driver, drivers::graphics_command_list_builder &builder);
        virtual egl_context_type context_type() const = 0;
        virtual void init_context_state(drivers::graphics_command_list_builder &builder) = 0;
    };

    using egl_context_instance = std::unique_ptr<egl_context>;
    using egl_surface_instance = std::unique_ptr<egl_surface>;
    using egl_context_handle = std::uint32_t;
    using egl_surface_handle = std::uint32_t;

    struct egl_controller {
    private:
        common::identity_container<egl_context_instance> contexts_;
        common::identity_container<egl_surface_instance> dsurfaces_;

        std::map<kernel::uid, egl_context *> active_context_;
        std::map<kernel::uid, std::uint32_t> error_map_;
        std::map<kernel::uid, std::uint32_t> egl_error_map_;

        gles1_shaderman es1_shaderman_;

        drivers::graphics_driver *driver_;

    public:
        explicit egl_controller(drivers::graphics_driver *driver);
        ~egl_controller();

        void set_graphics_driver(drivers::graphics_driver *driver);

        gles1_shaderman &get_es1_shaderman() {
            return es1_shaderman_;
        }

        std::uint32_t add_managed_surface(egl_surface_instance &inst);
        void destroy_managed_surface(const std::uint32_t handle);
        void remove_managed_surface_from_management(const egl_surface *surface);

        egl_surface *get_managed_surface(const std::uint32_t managed_handle);

        bool make_current(kernel::uid thread_id, const egl_context_handle handle);
        void clear_current(kernel::uid thread_id);

        egl_context_handle add_context(egl_context_instance &instance);
        void remove_context(const egl_context_handle handle);

        egl_context *current_context(kernel::uid thread_id);
        egl_context *get_context(const egl_context_handle handle);

        void push_error(kernel::uid thread_id, const std::uint32_t error);
        std::uint32_t pop_error(kernel::uid thread_id);

        void push_error(egl_context *context, const std::uint32_t error);
        std::uint32_t pop_error(egl_context *context);

        void push_egl_error(kernel::uid thread_id, const std::uint32_t error);
        std::uint32_t pop_egl_error(kernel::uid thread_id);
    };
}