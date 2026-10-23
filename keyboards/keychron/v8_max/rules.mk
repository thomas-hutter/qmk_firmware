include keyboards/keychron/common/wireless/wireless.mk
include keyboards/keychron/common/keychron_common.mk

CAPS_WORD_ENABLE = yes
COMBO_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes
REPEAT_KEY_ENABLE = yes
LEADER_ENABLE = yes
LAYER_LOCK_ENABLE = yes


SELECT_WORD_ENABLE ?= yes
ifeq ($(strip $(SELECT_WORD_ENABLE)), yes)
	OPT_DEFS += -DSELECT_WORD_ENABLE
	SRC += features/select_word.c
endif

VPATH += $(TOP_DIR)/keyboards/keychron
