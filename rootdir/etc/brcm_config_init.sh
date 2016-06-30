
# project ID
ZE550ML=23
ZE551ML=31
ZR550ML=28
ZX550ML=27
ZE551ML_CKD=30

BRCM_CFG_FILE_NAME="libnfc-brcm.conf"
BRCM_CHIP_CFG_FILE_NAME="libnfc-brcm-20795a20.conf"
BRCM_SYS_DIR="/etc/"
BRCM_DATA_DIR="/data/nfc/"

PROJ_ID_VAL=$(cat /sys/module/intel_mid_sfi/parameters/project_id)
COUNTRY=$(cat /factory/PhoneInfodisk/country_code)

log -p i -t brcm_config_init "PROJID: $PROJ_ID_VAL"

case "$PROJ_ID_VAL" in
"$ZE551ML" | "$ZE551ML_CKD")
        project_id_str="ze551ml"
	;;
"$ZX550ML")
	project_id_str="zx551ml"
	;;
*)
        project_id_str="ze551ml"
esac

loc_str=$(getprop persist.nfc.loc)
if [ $project_id_str = "ze551ml" ]; then
        if [ -z "$loc_str" ]; then
                case "$COUNTRY" in
                        "TW")
                                loc_str="tweccplm"
                                setprop persist.nfc.loc tweccplm
                                ;;
                        *)
                                loc_str="gold"
                                setprop persist.nfc.loc gold
                esac
        fi
fi
if [ $project_id_str = "zx551ml" ]; then
        if [ -z "$loc_str" ]; then
                loc_str="gold"
                setprop persist.nfc.loc gold
        fi
fi
log -p i -t brcm_config_init "project: $project_id_str, location: $loc_str"


BRCM_SYS_CFG_FILE_PATH="${BRCM_SYS_DIR}${project_id_str}_${loc_str}_${BRCM_CFG_FILE_NAME}"
BRCM_SYS_CHIP_CFG_FILE_PATH="${BRCM_SYS_DIR}${project_id_str}_${loc_str}_${BRCM_CHIP_CFG_FILE_NAME}"

BRCM_LNK_CFG_FILE_PATH=${BRCM_DATA_DIR}${BRCM_CFG_FILE_NAME}
BRCM_LNK_CHIP_CFG_FILE_PATH=${BRCM_DATA_DIR}${BRCM_CHIP_CFG_FILE_NAME}

log -p i -t brcm_config_init "link: $BRCM_LNK_CFG_FILE_PATH, target: $BRCM_SYS_CFG_FILE_PATH"
log -p i -t brcm_config_init "link: $BRCM_LNK_CHIP_CFG_FILE_PATH, target: $BRCM_SYS_CHIP_CFG_FILE_PATH"

log -p i -t brcm_config_init "delete ... "
rm -rf $BRCM_LNK_CFG_FILE_PATH
rm -rf $BRCM_LNK_CHIP_CFG_FILE_PATH

log -p i -t brcm_config_init "link ... "
ln -sf $BRCM_SYS_CFG_FILE_PATH $BRCM_LNK_CFG_FILE_PATH
ln -sf $BRCM_SYS_CHIP_CFG_FILE_PATH $BRCM_LNK_CHIP_CFG_FILE_PATH

log -p i -t brcm_config_init "setprop ... "
setprop sys.nfc.project_id_str "${project_id_str}"
setprop sys.nfc.loc "${loc_str}"
setprop sys.nfc.brcm.cfg "${BRCM_SYS_CFG_FILE_PATH}"
setprop sys.nfc.brcm.chip_cfg "${BRCM_SYS_CHIP_CFG_FILE_PATH}"


