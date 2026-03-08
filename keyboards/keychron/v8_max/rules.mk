include keyboards/keychron/common/wireless/wireless.mk
include keyboards/keychron/common/keychron_common.mk

CAPS_WORD_ENABLE = yes
USER_NUM_WORD_ENABLE = no
COMBO_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes
REPEAT_KEY_ENABLE = yes
LEADER_ENABLE = yes

ifeq ($(strip $(USER_NUM_WORD_ENABLE)), yes)
	OPT_DEFS += -DUSER_NUM_WORD_ENABLE
endif

ACHORDION_ENABLE ?= yes
ifeq ($(strip $(ACHORDION_ENABLE)), yes)
	OPT_DEFS += -DACHORDION_ENABLE
	SRC += features/achordion.c
endif

LAYER_LOCK_ENABLE ?= yes
ifeq ($(strip $(LAYER_LOCK_ENABLE)), yes)
	OPT_DEFS += -DLAYER_LOCK_ENABLE
	SRC += features/layer_lock.c
endif

SELECT_WORD_ENABLE ?= yes
ifeq ($(strip $(SELECT_WORD_ENABLE)), yes)
	OPT_DEFS += -DSELECT_WORD_ENABLE
	SRC += features/select_word.c
endif

VPATH += $(TOP_DIR)/keyboards/keychron