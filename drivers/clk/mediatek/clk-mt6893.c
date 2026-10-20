// SPDX-License-Identifier: GPL-2.0
/*
 * MT6893 infracfg_ao clock driver (bring-up version)
 *
 * Data derived from MT6885 source (OnePlus OSS), cross-checked against the
 * MT6893 device tree: UART0=23, UART1=24, UFS=80/63/65/81, MSDC0=31/33.
 * All 16 sampled IDs match MT6885 exactly.
 */

#include <linux/clk-provider.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <dt-bindings/clock/mt6893-clk.h>

#include "clk-gate.h"
#include "clk-mtk.h"

/* 4.19 的 GATE() 映射到 6.6 的 GATE_MTK() */
#define GATE(_id, _name, _parent, _regs, _shift, _flags) \
	GATE_MTK(_id, _name, _parent, &_regs, _shift, &mtk_clk_gate_ops_setclr)

static const struct mtk_gate_regs infracfg_ao_module_sw_cg_0_regs = {
	.set_ofs = 0x80,
	.clr_ofs = 0x84,
	.sta_ofs = 0x90,
};

static const struct mtk_gate_regs infracfg_ao_module_sw_cg_1_regs = {
	.set_ofs = 0x88,
	.clr_ofs = 0x8c,
	.sta_ofs = 0x94,
};

static const struct mtk_gate_regs infracfg_ao_module_sw_cg_2_regs = {
	.set_ofs = 0xa4,
	.clr_ofs = 0xa8,
	.sta_ofs = 0xac,
};

static const struct mtk_gate_regs infracfg_ao_module_sw_cg_3_regs = {
	.set_ofs = 0xc0,
	.clr_ofs = 0xc4,
	.sta_ofs = 0xc8,
};

static const struct mtk_gate_regs infracfg_ao_module_sw_cg_4_regs = {
	.set_ofs = 0xd0,
	.clr_ofs = 0xd4,
	.sta_ofs = 0xd8,
};

static const struct mtk_gate infra_clks[] __initconst = {
	/* MODULE_SW_CG_0 */
	GATE(INFRACFG_AO_PMIC_CG_TMR, "infracfg_ao_pmic_cg_tmr", "f26m_sel",
			 infracfg_ao_module_sw_cg_0_regs, 0, 0),
	GATE(INFRACFG_AO_PMIC_CG_AP, "infracfg_ao_pmic_cg_ap", "f26m_sel",
			 infracfg_ao_module_sw_cg_0_regs, 1, 0),
	GATE(INFRACFG_AO_PMIC_CG_MD, "infracfg_ao_pmic_cg_md", "f26m_sel",
			 infracfg_ao_module_sw_cg_0_regs, 2, 0),
	GATE(INFRACFG_AO_PMIC_CG_CONN, "infracfg_ao_pmic_cg_conn", "f26m_sel",
			 infracfg_ao_module_sw_cg_0_regs, 3, 0),
	GATE(INFRACFG_AO_SCPSYS_CG, "infracfg_ao_scpsys_cg", "clk_null",
			 infracfg_ao_module_sw_cg_0_regs, 4, 0),
	GATE(INFRACFG_AO_SEJ_CG, "infracfg_ao_sej_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_0_regs, 5, 0),
	GATE(INFRACFG_AO_APXGPT_CG, "infracfg_ao_apxgpt_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_0_regs, 6, 0),
	GATE(INFRACFG_AO_MCUPM_CG, "infracfg_ao_mcupm_cg", "mcupm_sel",
			 infracfg_ao_module_sw_cg_0_regs, 7, 0),
	GATE(INFRACFG_AO_GCE_CG, "infracfg_ao_gce_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_0_regs, 8, 0),
	GATE(INFRACFG_AO_GCE2_CG, "infracfg_ao_gce2_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_0_regs, 9, 0),
	GATE(INFRACFG_AO_THERM_CG, "infracfg_ao_therm_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_0_regs, 10, 0),
	GATE(INFRACFG_AO_I2C0_CG, "infracfg_ao_i2c0_cg", "i2c_sel",
			 infracfg_ao_module_sw_cg_0_regs, 11, 0),
	GATE(INFRACFG_AO_I2C1_CG, "infracfg_ao_i2c1_cg", "i2c_sel",
			 infracfg_ao_module_sw_cg_0_regs, 12, 0),
	GATE(INFRACFG_AO_I2C2_CG, "infracfg_ao_i2c2_cg", "i2c_sel",
			 infracfg_ao_module_sw_cg_0_regs, 13, 0),
	GATE(INFRACFG_AO_I2C3_CG, "infracfg_ao_i2c3_cg", "i2c_sel",
			 infracfg_ao_module_sw_cg_0_regs, 14, 0),
	GATE(INFRACFG_AO_PWM_HCLK_CG, "infracfg_ao_pwm_hclk_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_0_regs, 15, 0),
	GATE(INFRACFG_AO_PWM1_CG, "infracfg_ao_pwm1_cg", "pwm_sel",
			 infracfg_ao_module_sw_cg_0_regs, 16, 0),
	GATE(INFRACFG_AO_PWM2_CG, "infracfg_ao_pwm2_cg", "pwm_sel",
			 infracfg_ao_module_sw_cg_0_regs, 17, 0),
	GATE(INFRACFG_AO_PWM3_CG, "infracfg_ao_pwm3_cg", "pwm_sel",
			 infracfg_ao_module_sw_cg_0_regs, 18, 0),
	GATE(INFRACFG_AO_PWM4_CG, "infracfg_ao_pwm4_cg", "pwm_sel",
			 infracfg_ao_module_sw_cg_0_regs, 19, 0),
	GATE(INFRACFG_AO_PWM_CG, "infracfg_ao_pwm_cg", "pwm_sel",
			 infracfg_ao_module_sw_cg_0_regs, 21, 0),
	GATE(INFRACFG_AO_UART0_CG, "infracfg_ao_uart0_cg", "uart_sel",
			 infracfg_ao_module_sw_cg_0_regs, 22, 0),
	GATE(INFRACFG_AO_UART1_CG, "infracfg_ao_uart1_cg", "uart_sel",
			 infracfg_ao_module_sw_cg_0_regs, 23, 0),
	GATE(INFRACFG_AO_UART2_CG, "infracfg_ao_uart2_cg", "uart_sel",
			 infracfg_ao_module_sw_cg_0_regs, 24, 0),
	GATE(INFRACFG_AO_UART3_CG, "infracfg_ao_uart3_cg", "uart_sel",
			 infracfg_ao_module_sw_cg_0_regs, 25, 0),
	GATE(INFRACFG_AO_GCE_26M, "infracfg_ao_gce_26m", "axi_sel",
			 infracfg_ao_module_sw_cg_0_regs, 27, 0),
	GATE(INFRACFG_AO_CQ_DMA_FPC, "infracfg_ao_cq_dma_fpc", "axi_sel",
			 infracfg_ao_module_sw_cg_0_regs, 28, 0),
	GATE(INFRACFG_AO_BTIF_CG, "infracfg_ao_btif_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_0_regs, 31, 0),
	/* MODULE_SW_CG_1 */
	GATE(INFRACFG_AO_SPI0_CG, "infracfg_ao_spi0_cg", "spi_sel",
			 infracfg_ao_module_sw_cg_1_regs, 1, 0),
	GATE(INFRACFG_AO_MSDC0_CG, "infracfg_ao_msdc0_cg", "msdc50_0_hclk_sel",
			 infracfg_ao_module_sw_cg_1_regs, 2, 0),
	GATE(INFRACFG_AO_MSDC1_CG, "infracfg_ao_msdc1_cg", "msdc50_0_hclk_sel",
			 infracfg_ao_module_sw_cg_1_regs, 4, 0),
	GATE(INFRACFG_AO_MSDC0_SRC_CLK_CG, "infracfg_ao_msdc0_src_clk_cg",
			"msdc50_0_sel",
			 infracfg_ao_module_sw_cg_1_regs, 6, 0),
	GATE(INFRACFG_AO_DVFSRC_CG, "infracfg_ao_dvfsrc_cg", "f26m_sel",
			 infracfg_ao_module_sw_cg_1_regs, 7, 0),
	GATE(INFRACFG_AO_GCPU_CG, "infracfg_ao_gcpu_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_1_regs, 8, 0),
	GATE(INFRACFG_AO_TRNG_CG, "infracfg_ao_trng_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_1_regs, 9, 0),
	GATE(INFRACFG_AO_AUXADC_CG, "infracfg_ao_auxadc_cg",
			"f26m_sel",
			 infracfg_ao_module_sw_cg_1_regs, 10, 0),
	GATE(INFRACFG_AO_CPUM_CG, "infracfg_ao_cpum_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_1_regs, 11, 0),
	GATE(INFRACFG_AO_CCIF1_AP_CG, "infracfg_ao_ccif1_ap_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_1_regs, 12, 0),
	GATE(INFRACFG_AO_CCIF1_MD_CG, "infracfg_ao_ccif1_md_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_1_regs, 13, 0),
	GATE(INFRACFG_AO_AUXADC_MD_CG, "infracfg_ao_auxadc_md_cg",
			"f26m_sel",
			 infracfg_ao_module_sw_cg_1_regs, 14, 0),
	GATE(INFRACFG_AO_MSDC1_SRC_CLK_CG, "infracfg_ao_msdc1_src_clk_cg",
			"msdc30_1_sel",
			 infracfg_ao_module_sw_cg_1_regs, 16, 0),
	GATE(INFRACFG_AO_AP_DMA_PSEUDO_CG, "infracfg_ao_ap_dma_pseudo_cg",
			"axi_sel",	/* add manually */
			 infracfg_ao_module_sw_cg_1_regs, 18, 0),
	GATE(INFRACFG_AO_DEVICE_APC_CG, "infracfg_ao_device_apc_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_1_regs, 20, 0),
	GATE(INFRACFG_AO_CCIF_AP_CG, "infracfg_ao_ccif_ap_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_1_regs, 23, 0),
	GATE(INFRACFG_AO_DEBUGSYS_CG, "infracfg_ao_debugsys_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_1_regs, 24, 0),
	GATE(INFRACFG_AO_AUDIO_CG, "infracfg_ao_audio_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_1_regs, 25, 0),
	GATE(INFRACFG_AO_CCIF_MD_CG, "infracfg_ao_ccif_md_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_1_regs, 26, 0),
	GATE(INFRACFG_AO_DXCC_SEC_CORE_CG, "infracfg_ao_dxcc_sec_core_cg",
			"dxcc_sel",
			 infracfg_ao_module_sw_cg_1_regs, 27, 0),
	GATE(INFRACFG_AO_DXCC_AO_CG, "infracfg_ao_dxcc_ao_cg", "dxcc_sel",
			 infracfg_ao_module_sw_cg_1_regs, 28, 0),
	GATE(INFRACFG_AO_DBG_TRACE_CG, "infracfg_ao_dbg_trace_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_1_regs, 29, 0),
	GATE(INFRACFG_AO_DEVMPU_BCLK_CG, "infracfg_ao_devmpu_bclk_cg",
			"axi_sel",
			 infracfg_ao_module_sw_cg_1_regs, 30, 0),
	GATE(INFRACFG_AO_DRAMC_F26M_CG, "infracfg_ao_dramc_f26m_cg", "f26m_sel",
			 infracfg_ao_module_sw_cg_1_regs, 31, 0),
	/* MODULE_SW_CG_2 */
	GATE(INFRACFG_AO_IRTX_CG, "infracfg_ao_irtx_cg", "f26m_sel",
			 infracfg_ao_module_sw_cg_2_regs, 0, 0),
	GATE(INFRACFG_AO_SSUSB_CG, "infracfg_ao_ssusb_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_2_regs, 1, 0),
	GATE(INFRACFG_AO_DISP_PWM_CG, "infracfg_ao_disp_pwm_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_2_regs, 2, 0),
	GATE(INFRACFG_AO_CLDMA_BCLK_CK, "infracfg_ao_cldma_bclk_ck", "axi_sel",
			 infracfg_ao_module_sw_cg_2_regs, 3, 0),
	GATE(INFRACFG_AO_AUDIO_26M_BCLK_CK, "infracfg_ao_audio_26m_bclk_ck",
			"f26m_sel",
			 infracfg_ao_module_sw_cg_2_regs, 4, 0),
	GATE(INFRACFG_AO_MODEM_TEMP_SHARE_CG, "infracfg_ao_modem_temp_share_cg",
			"f26m_sel",
			 infracfg_ao_module_sw_cg_2_regs, 5, 0),
	GATE(INFRACFG_AO_SPI1_CG, "infracfg_ao_spi1_cg", "spi_sel",
			 infracfg_ao_module_sw_cg_2_regs, 6, 0),
	GATE(INFRACFG_AO_I2C4_CG, "infracfg_ao_i2c4_cg", "i2c_sel",
			 infracfg_ao_module_sw_cg_2_regs, 7, 0),
	GATE(INFRACFG_AO_SPI2_CG, "infracfg_ao_spi2_cg", "spi_sel",
			 infracfg_ao_module_sw_cg_2_regs, 9, 0),
	GATE(INFRACFG_AO_SPI3_CG, "infracfg_ao_spi3_cg", "spi_sel",
			 infracfg_ao_module_sw_cg_2_regs, 10, 0),
	GATE(INFRACFG_AO_UNIPRO_SYSCLK_CG, "infracfg_ao_unipro_sysclk_cg",
			"ufs_sel",
			 infracfg_ao_module_sw_cg_2_regs, 11, 0),
	GATE(INFRACFG_AO_UNIPRO_TICK_CG, "infracfg_ao_unipro_tick_cg",
			"f26m_sel",
			 infracfg_ao_module_sw_cg_2_regs, 12, 0),
	GATE(INFRACFG_AO_UFS_MP_SAP_BCLK_CG, "infracfg_ao_ufs_mp_sap_bclk_cg",
			"f26m_sel",
			 infracfg_ao_module_sw_cg_2_regs, 13, 0),
	GATE(INFRACFG_AO_MD32_BCLK_CG, "infracfg_ao_md32_bclk_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_2_regs, 14, 0),
	GATE(INFRACFG_AO_SSPM_CG, "infracfg_ao_sspm_cg", "sspm_sel",
			 infracfg_ao_module_sw_cg_2_regs, 15, 0),
	GATE(INFRACFG_AO_UNIPRO_MBIST_CG, "infracfg_ao_unipro_mbist_cg",
			"axi_sel",
			 infracfg_ao_module_sw_cg_2_regs, 16, 0),
	GATE(INFRACFG_AO_SSPM_BUS_HCLK_CG, "infracfg_ao_sspm_bus_hclk_cg",
			"axi_sel",
			 infracfg_ao_module_sw_cg_2_regs, 17, 0),
	GATE(INFRACFG_AO_I2C5_CG, "infracfg_ao_i2c5_cg", "i2c_sel",
			 infracfg_ao_module_sw_cg_2_regs, 18, 0),
	GATE(INFRACFG_AO_I2C5_ARBITER_CG, "infracfg_ao_i2c5_arbiter_cg",
			"i2c_sel",
			 infracfg_ao_module_sw_cg_2_regs, 19, 0),
	GATE(INFRACFG_AO_I2C5_IMM_CG, "infracfg_ao_i2c5_imm_cg", "i2c_sel",
			 infracfg_ao_module_sw_cg_2_regs, 20, 0),
	GATE(INFRACFG_AO_I2C1_ARBITER_CG, "infracfg_ao_i2c1_arbiter_cg",
			"i2c_sel",
			 infracfg_ao_module_sw_cg_2_regs, 21, 0),
	GATE(INFRACFG_AO_I2C1_IMM_CG, "infracfg_ao_i2c1_imm_cg", "i2c_sel",
			 infracfg_ao_module_sw_cg_2_regs, 22, 0),
	GATE(INFRACFG_AO_I2C2_ARBITER_CG, "infracfg_ao_i2c2_arbiter_cg",
			"i2c_sel",
			 infracfg_ao_module_sw_cg_2_regs, 23, 0),
	GATE(INFRACFG_AO_I2C2_IMM_CG, "infracfg_ao_i2c2_imm_cg", "i2c_sel",
			 infracfg_ao_module_sw_cg_2_regs, 24, 0),
	GATE(INFRACFG_AO_SPI4_CG, "infracfg_ao_spi4_cg", "spi_sel",
			 infracfg_ao_module_sw_cg_2_regs, 25, 0),
	GATE(INFRACFG_AO_SPI5_CG, "infracfg_ao_spi5_cg", "spi_sel",
			 infracfg_ao_module_sw_cg_2_regs, 26, 0),
	GATE(INFRACFG_AO_CQ_DMA_CG, "infracfg_ao_cq_dma_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_2_regs, 27, 0),
	GATE(INFRACFG_AO_UFS_CG, "infracfg_ao_ufs_cg", "ufs_sel",
			 infracfg_ao_module_sw_cg_2_regs, 28, 0),
	GATE(INFRACFG_AO_AES_UFSFDE_CG, "infracfg_ao_aes_cg", "aes_ufsfde_sel",
			 infracfg_ao_module_sw_cg_2_regs, 29, 0),
	GATE(INFRACFG_AO_UFS_TICK_CG, "infracfg_ao_ufs_tick_cg", "ufs_sel",
			 infracfg_ao_module_sw_cg_2_regs, 30, 0),
	GATE(INFRACFG_AO_SSUSB_XHCI_CG, "infracfg_ao_ssusb_xhci_cg",
			"ssusb_xhci_sel",
			 infracfg_ao_module_sw_cg_2_regs, 31, 0),
	/* MODULE_SW_CG_3 */
	GATE(INFRACFG_AO_MSDC0_SELF_CG, "infracfg_ao_msdc0_self_cg",
			"msdc50_0_sel",
			 infracfg_ao_module_sw_cg_3_regs, 0, 0),
	GATE(INFRACFG_AO_MSDC1_SELF_CG, "infracfg_ao_msdc1_self_cg",
			"msdc50_0_sel",
			 infracfg_ao_module_sw_cg_3_regs, 1, 0),
	GATE(INFRACFG_AO_MSDC2_SELF_CG, "infracfg_ao_msdc2_self_cg",
			"msdc50_0_sel",
			 infracfg_ao_module_sw_cg_3_regs, 2, 0),
	GATE(INFRACFG_AO_SSPM_26M_SELF_CG, "infracfg_ao_sspm_26m_self_cg",
			"f26m_sel",
			 infracfg_ao_module_sw_cg_3_regs, 3, 0),
	GATE(INFRACFG_AO_SSPM_32K_SELF_CG, "infracfg_ao_sspm_32k_self_cg",
			"clk32k",
			 infracfg_ao_module_sw_cg_3_regs, 4, 0),
	GATE(INFRACFG_AO_UFS_AXI_CG, "infracfg_ao_ufs_axi_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_3_regs, 5, 0),
	GATE(INFRACFG_AO_I2C6_CG, "infracfg_ao_i2c6_cg", "i2c_sel",
			 infracfg_ao_module_sw_cg_3_regs, 6, 0),
	GATE(INFRACFG_AO_AP_MSDC0_CG, "infracfg_ao_ap_msdc0_cg",
			"msdc50_0_sel",
			 infracfg_ao_module_sw_cg_3_regs, 7, 0),
	GATE(INFRACFG_AO_MD_MSDC0_CG, "infracfg_ao_md_msdc0_cg",
			"msdc50_0_sel",
			 infracfg_ao_module_sw_cg_3_regs, 8, 0),
	GATE(INFRACFG_AO_CCIF5_AP_CG, "infracfg_ao_ccif5_ap_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_3_regs, 9, 0),
	GATE(INFRACFG_AO_CCIF5_MD_CG, "infracfg_ao_ccif5_md_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_3_regs, 10, 0),
	GATE(INFRACFG_AO_CCIF2_AP_CG, "infracfg_ao_ccif2_ap_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_3_regs, 16, 0),
	GATE(INFRACFG_AO_CCIF2_MD_CG, "infracfg_ao_ccif2_md_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_3_regs, 17, 0),
	GATE(INFRACFG_AO_CCIF3_AP_CG, "infracfg_ao_ccif3_ap_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_3_regs, 18, 0),
	GATE(INFRACFG_AO_CCIF3_MD_CG, "infracfg_ao_ccif3_md_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_3_regs, 19, 0),
	GATE(INFRACFG_AO_SEJ_F13M_CG, "infracfg_ao_sej_f13m_cg", "f26m_sel",
			 infracfg_ao_module_sw_cg_3_regs, 20, 0),
	GATE(INFRACFG_AO_AES_CG, "infracfg_ao_aes_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_3_regs, 21, 0),
	GATE(INFRACFG_AO_I2C7_CG, "infracfg_ao_i2c7_cg", "i2c_sel",
			 infracfg_ao_module_sw_cg_3_regs, 22, 0),
	GATE(INFRACFG_AO_I2C8_CG, "infracfg_ao_i2c8_cg", "i2c_sel",
			 infracfg_ao_module_sw_cg_3_regs, 23, 0),
	GATE(INFRACFG_AO_FBIST2FPC_CG, "infracfg_ao_fbist2fpc_cg",
			"msdc50_0_sel",
			 infracfg_ao_module_sw_cg_3_regs, 24, 0),
	GATE(INFRACFG_AO_DEVICE_APC_SYNC_CG, "infracfg_ao_device_apc_sync_cg",
			"axi_sel",
			 infracfg_ao_module_sw_cg_3_regs, 25, 0),
	GATE(INFRACFG_AO_DPMAIF_MAIN_CG, "infracfg_ao_dpmaif_main_cg",
			"dpmaif_main_sel",
			infracfg_ao_module_sw_cg_3_regs, 26, 0),
	GATE(INFRACFG_AO_CCIF4_AP_CG, "infracfg_ao_ccif4_ap_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_3_regs, 28, 0),
	GATE(INFRACFG_AO_CCIF4_MD_CG, "infracfg_ao_ccif4_md_cg", "axi_sel",
			 infracfg_ao_module_sw_cg_3_regs, 29, 0),
	GATE(INFRACFG_AO_SPI6_CK_CG, "infracfg_ao_spi6_ck_cg", "spi_sel",
			 infracfg_ao_module_sw_cg_3_regs, 30, 0),
	GATE(INFRACFG_AO_SPI7_CK_CG, "infracfg_ao_spi7_ck_cg", "spi_sel",
			 infracfg_ao_module_sw_cg_3_regs, 31, 0),

	/* MODULE_SW_CG_4 */
/*	GATE(INFRACFG_AO_AP_DMA_CG, "infracfg_ao_ap_dma_cg", "axi_sel",
 *			infracfg_ao_module_sw_cg_4_regs, 31, 0),
 */
	/*
	 * MT6885: pll -> mux -> iic_cg(pseudo) -> iic_cg
	 * This is a workaround for MT6885.
	 *
	 * IIC_CG(PSEUDO) : the signal bit for SPM
	 * IIC_CG: the signal bit that real clock gating.
	 */
	GATE(INFRACFG_AO_AP_DMA_CG, "infracfg_ao_ap_dma_cg",
			"infracfg_ao_ap_dma_pseudo_cg",
			infracfg_ao_module_sw_cg_4_regs, 31, 0),
};

static void __init mtk_infracfg_ao_init(struct device_node *node)
{
	struct clk_hw_onecell_data *clk_data;
	int i, ret;

	clk_data = mtk_alloc_clk_data(INFRACFG_AO_NR_CLK);
	if (!clk_data)
		return;

	/* 父时钟占位：真实 PLL 已由 lk 初始化，这里只是让 gate 能注册 */
	for (i = 0; i < ARRAY_SIZE(infra_clks); i++) {
		if (!infra_clks[i].parent_name)
			continue;
		clk_register_fixed_rate(NULL, infra_clks[i].parent_name,
					NULL, 0, 26000000);
	}

	ret = mtk_clk_register_gates(NULL, node, infra_clks,
				     ARRAY_SIZE(infra_clks), clk_data);
	if (ret) {
		pr_err("mt6893: register infracfg_ao gates failed: %d\n", ret);
		return;
	}

	ret = of_clk_add_hw_provider(node, of_clk_hw_onecell_get, clk_data);
	if (ret)
		pr_err("mt6893: add clk provider failed: %d\n", ret);
}
CLK_OF_DECLARE_DRIVER(mtk_infracfg_ao, "mediatek,infracfg_ao",
		      mtk_infracfg_ao_init);
