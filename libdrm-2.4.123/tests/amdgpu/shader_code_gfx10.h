/*
 * Copyright 2022 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
*/

#ifndef _shader_code_gfx10_h_
#define _shader_code_gfx10_h_

static const uint32_t bufferclear_cs_shader_gfx10[] = {
	0xD7460004, 0x04010C08, 0x7E000204, 0x7E020205,
	0x7E040206, 0x7E060207, 0xE01C2000, 0x80000004,
	0xBF810000
};

static const uint32_t buffercopy_cs_shader_gfx10[] = {
	0xD7460001, 0x04010C08, 0xE00C2000, 0x80000201,
	0xBF8C3F70, 0xE01C2000, 0x80010201, 0xBF810000
};

static const uint32_t ps_const_shader_gfx10[] = {
    0x7E000200, 0x7E020201, 0x7E040202, 0x7E060203,
    0x5E000300, 0x5E020702, 0xBF800000, 0xBF800000,
    0xF8001C0F, 0x00000100, 0xBF810000
};

#define ps_const_shader_patchinfo_code_size_gfx10 6

static const uint32_t ps_const_shader_patchinfo_code_gfx10[][10][6] = {
    {{ 0xBF800000, 0xBF800000, 0xBF800000, 0xBF800000, 0xF8001890, 0x00000000 },
     { 0xBF800000, 0xBF800000, 0xBF800000, 0xBF800000, 0xF8001801, 0x00000000 },
     { 0xBF800000, 0xBF800000, 0xBF800000, 0xBF800000, 0xF8001803, 0x00000100 },
     { 0xBF800000, 0xBF800000, 0xBF800000, 0xBF800000, 0xF8001803, 0x00000300 },
     { 0x5E000300, 0x5E020702, 0xBF800000, 0xBF800000, 0xF8001C0F, 0x00000100 },
     { 0xD7690000, 0x00020300, 0xD7690001, 0x00020702, 0xF8001C0F, 0x00000100 },
     { 0xD7680000, 0x00020300, 0xD7680001, 0x00020702, 0xF8001C0F, 0x00000100 },
     { 0xD76A0000, 0x00020300, 0xD76A0001, 0x00020702, 0xF8001C0F, 0x00000100 },
     { 0xD76B0000, 0x00020300, 0xD76B0001, 0x00020702, 0xF8001C0F, 0x00000100 },
     { 0xBF800000, 0xBF800000, 0xBF800000, 0xBF800000, 0xF800180F, 0x03020100 }
    }
};

static const uint32_t ps_const_shader_patchinfo_offset_gfx10[] = {
    0x00000004
};

#define ps_const_num_sh_registers_gfx10 2

static const struct reg_info ps_const_sh_registers_gfx10[] = {
	{0x2C0A, 0x000C0000},//{ mmSPI_SHADER_PGM_RSRC1_PS, 0x000C0000 },
	{0x2C0B, 0x00000008}, //{ mmSPI_SHADER_PGM_RSRC2_PS, 0x00000008 }
};

static const struct reg_info ps_const_context_registers_gfx10[] =
{
    {0xA1B4, 0x00000002}, //{ mmSPI_PS_INPUT_ADDR,       0x00000002 },
    {0xA1B6, 0x00000000}, //{ mmSPI_PS_IN_CONTROL,       0x00000000 },
    {0xA08F, 0x0000000F}, //{ mmCB_SHADER_MASK,          0x0000000F },
    {0xA203, 0x00000010}, //{ mmDB_SHADER_CONTROL,       0x00000010 },
    {0xA1C4, 0x00000000}, //{ mmSPI_SHADER_Z_FORMAT,     0x00000000 },
    {0xA1B8, 0x00000000}, //{ mmSPI_BARYC_CNTL,          0x00000000 /* Always 0 for now */},
    {0xA1C5, 0x00000004}, //{ mmSPI_SHADER_COL_FORMAT,   0x00000004 /* SI_EXPORT_FMT_FP16_ABGR */ }
};

#define ps_const_num_context_registers_gfx10 7

static const uint32_t ps_tex_shader_gfx10[] = {
    0xBEFC030C, 0xBE8E047E, 0xBEFE0A7E, 0xC8080000,
    0xC80C0100, 0xC8090001, 0xC80D0101, 0xF0800F0A,
    0x00400402, 0x00000003, 0xBEFE040E, 0xBF8C0F70,
    0x5E000B04, 0x5E020F06, 0xBF800000, 0xBF800000,
    0xF8001C0F, 0x00000100, 0xBF810000
};

static const uint32_t ps_tex_shader_patchinfo_offset_gfx10[] = {
    0x0000000C
};

#define ps_tex_shader_patchinfo_code_size_gfx10 6

static const uint32_t ps_tex_shader_patchinfo_code_gfx10[][10][6] = {
    {{ 0xBF800000, 0xBF800000, 0xBF800000, 0xBF800000, 0xF8001890, 0x00000000 },
     { 0xBF800000, 0xBF800000, 0xBF800000, 0xBF800000, 0xF8001801, 0x00000004 },
     { 0xBF800000, 0xBF800000, 0xBF800000, 0xBF800000, 0xF8001803, 0x00000504 },
     { 0xBF800000, 0xBF800000, 0xBF800000, 0xBF800000, 0xF8001803, 0x00000704 },
     { 0x5E000B04, 0x5E020F06, 0xBF800000, 0xBF800000, 0xF8001C0F, 0x00000100 },
     { 0xD7690000, 0x00020B04, 0xD7690001, 0x00020F06, 0xF8001C0F, 0x00000100 },
     { 0xD7680000, 0x00020B04, 0xD7680001, 0x00020F06, 0xF8001C0F, 0x00000100 },
     { 0xD76A0000, 0x00020B04, 0xD76A0001, 0x00020F06, 0xF8001C0F, 0x00000100 },
     { 0xD76B0000, 0x00020B04, 0xD76B0001, 0x00020F06, 0xF8001C0F, 0x00000100 },
     { 0xBF800000, 0xBF800000, 0xBF800000, 0xBF800000, 0xF800180F, 0x07060504 }
    }
};

static const struct reg_info ps_tex_sh_registers_gfx10[] =
{
     {0x2C0A, 0xc0081}, //0x020C0080 }, //{ mmSPI_SHADER_PGM_RSRC1_PS, 0x020C0080 },
     {0x2C0B, 0x00000018 }, //{ mmSPI_SHADER_PGM_RSRC2_PS, 0x00000018 }
};

#define ps_tex_num_sh_registers_gfx10 2

// Holds Context Register Information
static const struct reg_info ps_tex_context_registers_gfx10[] =
{
    {0xA1B4, 0x00000002}, //{ mmSPI_PS_INPUT_ADDR,       0x00000002 },
    {0xA1B6, 0x00000001}, //{ mmSPI_PS_IN_CONTROL,       0x00000001 },
    {0xA08F, 0x0000000F}, //{ mmCB_SHADER_MASK,          0x0000000F },
    {0xA203, 0x00000010}, //{ mmDB_SHADER_CONTROL,       0x00000010 },
    {0xA1C4, 0x00000000}, //{ mmSPI_SHADER_Z_FORMAT,     0x00000000 },
    {0xA1B8, 0x00000000}, //{ mmSPI_BARYC_CNTL,          0x00000000 /* Always 0 for now */},
    {0xA1C5, 0x00000004}, //{ mmSPI_SHADER_COL_FORMAT,   0x00000004 /* SI_EXPORT_FMT_FP16_ABGR */ }
};

#define ps_tex_num_context_registers_gfx10 7

static const uint32_t vs_RectPosTexFast_shader_gfx10[] = {
    0x7E000B00, 0x060000F3, 0x7E020202, 0x7E040206,
    0x7C040080, 0x060000F3, 0xD5010001, 0x01AA0200,
    0x7E060203, 0xD5010002, 0x01AA0404, 0x7E080207,
    0x7C040080, 0xD5010000, 0x01A80101, 0xD5010001,
    0x01AA0601, 0x7E060208, 0x7E0A02F2, 0xD5010002,
    0x01A80902, 0xD5010004, 0x01AA0805, 0x7E0C0209,
    0xF80008CF, 0x05030100, 0xF800020F, 0x05060402,
    0xBF810000
};

static const struct reg_info vs_RectPosTexFast_sh_registers_gfx10[] =
{
    {0x2C4A, 0x080C0041 }, //{ mmSPI_SHADER_PGM_RSRC1_VS, 0x080C0041 },
    {0x2C4B, 0x00000018 }, //{ mmSPI_SHADER_PGM_RSRC2_VS, 0x00000018 }
};

#define vs_RectPosTexFast_num_sh_registers_gfx10 2

// Holds Context Register Information
static const struct reg_info vs_RectPosTexFast_context_registers_gfx10[] =
{
    {0xA1B1, 0x00000000}, //{ mmSPI_VS_OUT_CONFIG, 0x00000000 },
    {0xA1C3, 0x00000000}, //{ mmSPI_SHADER_POS_FORMAT, 0x00000000 /* Always 0 for now */}
};

#define vs_RectPosTexFast_num_context_registers_gfx10 2

static const uint32_t preamblecache_gfx10[] = {
	0xc0026900, 0x81, 0x80000000, 0x40004000, 0xc0026900, 0x8c, 0xaa99aaaa, 0x0,
	0xc0026900, 0x90, 0x80000000, 0x40004000, 0xc0026900, 0x94, 0x80000000, 0x40004000,
	0xc0026900, 0xb4, 0x0, 0x3f800000, 0xc0016900, 0x103, 0x0,
	0xc0016900, 0x208, 0x0, 0xc0016900, 0x290, 0x0,
	0xc0016900, 0x2a1, 0x0, 0xc0026900, 0x2ad, 0x0, 0x0,
	0xc0016900, 0x2d5, 0x10000, 0xc0016900, 0x2dc, 0x0,
	0xc0066900, 0x2de, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc0026900, 0x2e5, 0x0, 0x0,
	0xc0056900, 0x2f9, 0x5, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000,
	0xc0046900, 0x310, 0, 0x3, 0, 0x100000, 0xc0026900, 0x316, 0xe, 0x20,
	0xc0016900, 0x349, 0x0, 0xc0016900, 0x358, 0x0, 0xc0016900, 0x367, 0x0,
	0xc0016900, 0x376, 0x0, 0xc0016900, 0x385, 0x0, 0xc0016900, 0x6, 0x0,
	0xc0056900, 0xe8, 0x0, 0x0, 0x0, 0x0, 0x0,
	0xc0076900, 0x1e1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0xc0026900, 0x204, 0x90000, 0x4, 0xc0046900, 0x20c, 0x0, 0x0, 0x0, 0x0,
	0xc0016900, 0x2b2, 0x0, 0xc0026900, 0x30e, 0xffffffff, 0xffffffff,
	0xc0016900, 0x314, 0x0, 0xc0016900, 0x10a, 0, 0xc0016900, 0x2a6, 0, 0xc0016900, 0x210, 0,
	0xc0016900, 0x2db, 0, 0xc0016900, 0x1d4, 0, 0xc0002f00, 0x1, 0xc0016900, 0x1, 0x1, 0xc0016900, 0xe, 0x2,
	0xc0016900, 0x206, 0x300, 0xc0016900, 0x212, 0x200, 0xc0017900, 0x7b, 0x20, 0xc0017a00, 0x20000243, 0x0,
	0xc0017900, 0x249, 0, 0xc0017900, 0x24a, 0, 0xc0017900, 0x24b, 0, 0xc0017900, 0x259, 0xffffffff,
	0xc0017900, 0x25f, 0, 0xc0017900, 0x260, 0, 0xc0017900, 0x262, 0,
	0xc0017600, 0x45, 0x0, 0xc0017600, 0x6, 0x0,
	0xc0067600, 0x70, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0xc0067600, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
};

static const uint32_t cached_cmd_gfx10[] = {
	0xc0016900, 0x0, 0x0, 0xc0026900, 0x3, 0x2a, 0x0,
	0xc0046900, 0xa, 0x0, 0x0, 0x0, 0x200020,
	0xc0016900, 0x83, 0xffff, 0xc0026900, 0x8e, 0xf, 0xf,
	0xc0056900, 0x105, 0x0, 0x0, 0x0, 0x0, 0x18,
	0xc0026900, 0x10b, 0x0, 0x0, 0xc0016900, 0x1e0, 0x0,
	0xc0036900, 0x200, 0x0, 0x10000, 0xcc0011,
	0xc0026900, 0x292, 0x20, 0x6020000,
	0xc0026900, 0x2b0, 0x0, 0x0, 0xc0016900, 0x2f8, 0x0
};

#define sh_reg_base_gfx10 0x2C00
#define context_reg_base_gfx10 0xA000

#endif