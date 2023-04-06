##############################################
#                                            #
# ポケモン青用メイクファイル Version 1.3.0   #
# Coded by Teruki Murakawa                   #
# Copyright(C) 1998 Nintendo Co.,Ltd.        #
#                                            #
##############################################
.SUFFIXES:
.SUFFIXES: .isx .iso .dmg .def


#
#
MASM = isdmg
LINK = islink
SRC_DIR = Source
OBJ_DIR = Debug
TMP_DIR = Temp
LFLAGS = /W0/M
LINKFILE = ..\link.lnk

###############################################
# OBJS リストのフォーマット                   #
#    不要なタブやスペースを入れてはいけない！ #
# OBJS =\                                     #
# $(OBJ_DIR)\??????.iso[Tab]\                 #
###############################################

OBJS =\
$(OBJ_DIR)\common.iso	\
$(OBJ_DIR)\header.iso	\
$(OBJ_DIR)\bank.iso	\
$(OBJ_DIR)\mushead.iso	\
$(OBJ_DIR)\mushead2.iso	\
$(OBJ_DIR)\mushead3.iso	\
$(OBJ_DIR)\pattern.iso	\
$(OBJ_DIR)\cont.iso	\
$(OBJ_DIR)\waza.iso	\
$(OBJ_DIR)\mapper.iso	\
$(OBJ_DIR)\maporg.iso	\
$(OBJ_DIR)\data_box.iso	\
$(OBJ_DIR)\monster.iso	\
$(OBJ_DIR)\fight.iso	\
$(OBJ_DIR)\zukan.iso	\
$(OBJ_DIR)\dealer.iso	\
$(OBJ_DIR)\main.iso	\
$(OBJ_DIR)\mapsub.iso	\
$(OBJ_DIR)\effecter.iso	\
$(OBJ_DIR)\monslist.iso	\
$(OBJ_DIR)\item.iso	\
$(OBJ_DIR)\badge.iso	\
$(OBJ_DIR)\actput.iso	\
$(OBJ_DIR)\dma.iso	\
$(OBJ_DIR)\lcdc.iso	\
$(OBJ_DIR)\chrset.iso	\
$(OBJ_DIR)\print.iso	\
$(OBJ_DIR)\prt.iso	\
$(OBJ_DIR)\reset.iso	\
$(OBJ_DIR)\vblank.iso	\
$(OBJ_DIR)\sio.iso	\
$(OBJ_DIR)\timer.iso	\
$(OBJ_DIR)\play.iso	\
$(OBJ_DIR)\actor.iso	\
$(OBJ_DIR)\hitcheck.iso	\
$(OBJ_DIR)\itemmenu.iso	\
$(OBJ_DIR)\vanish.iso	\
$(OBJ_DIR)\debug.iso	\
$(OBJ_DIR)\commsg.iso	\
$(OBJ_DIR)\uncomp.iso	\
$(OBJ_DIR)\watashi.iso	\
$(OBJ_DIR)\a_move.iso	\
$(OBJ_DIR)\play2.iso	\
$(OBJ_DIR)\play1.iso	\
$(OBJ_DIR)\fadeplay.iso	\
$(OBJ_DIR)\talkmap.iso	\
$(OBJ_DIR)\objset.iso	\
$(OBJ_DIR)\encount.iso	\
$(OBJ_DIR)\useitem.iso	\
$(OBJ_DIR)\sfx.iso	\
$(OBJ_DIR)\town01.iso	\
$(OBJ_DIR)\town02.iso	\
$(OBJ_DIR)\town03.iso	\
$(OBJ_DIR)\town04.iso	\
$(OBJ_DIR)\town05.iso	\
$(OBJ_DIR)\town06.iso	\
$(OBJ_DIR)\town07.iso	\
$(OBJ_DIR)\town08.iso	\
$(OBJ_DIR)\town09.iso	\
$(OBJ_DIR)\town11.iso	\
$(OBJ_DIR)\road01.iso	\
$(OBJ_DIR)\road02.iso	\
$(OBJ_DIR)\road03.iso	\
$(OBJ_DIR)\road04.iso	\
$(OBJ_DIR)\road05.iso	\
$(OBJ_DIR)\road06.iso	\
$(OBJ_DIR)\road07.iso	\
$(OBJ_DIR)\road08.iso	\
$(OBJ_DIR)\road09.iso	\
$(OBJ_DIR)\road10.iso	\
$(OBJ_DIR)\road11.iso	\
$(OBJ_DIR)\road12.iso	\
$(OBJ_DIR)\road13.iso	\
$(OBJ_DIR)\road14.iso	\
$(OBJ_DIR)\road15.iso	\
$(OBJ_DIR)\road16.iso	\
$(OBJ_DIR)\road17.iso	\
$(OBJ_DIR)\road18.iso	\
$(OBJ_DIR)\road19.iso	\
$(OBJ_DIR)\road20.iso	\
$(OBJ_DIR)\road21.iso	\
$(OBJ_DIR)\road22.iso	\
$(OBJ_DIR)\road23.iso	\
$(OBJ_DIR)\road24.iso	\
$(OBJ_DIR)\road25.iso	\
$(OBJ_DIR)\t00r0101.iso	\
$(OBJ_DIR)\t00r0102.iso	\
$(OBJ_DIR)\t01r0101.iso	\
$(OBJ_DIR)\t01r0102.iso	\
$(OBJ_DIR)\t01r0201.iso	\
$(OBJ_DIR)\t01r0301.iso	\
$(OBJ_DIR)\t02r0101.iso	\
$(OBJ_DIR)\t02r0201.iso	\
$(OBJ_DIR)\t02r0301.iso	\
$(OBJ_DIR)\t02r0401.iso	\
$(OBJ_DIR)\t02r0501.iso	\
$(OBJ_DIR)\t03r0101.iso	\
$(OBJ_DIR)\t03r0102.iso	\
$(OBJ_DIR)\t03r0201.iso	\
$(OBJ_DIR)\t03r0301.iso	\
$(OBJ_DIR)\t03r0401.iso	\
$(OBJ_DIR)\t03r0501.iso	\
$(OBJ_DIR)\t03r0601.iso	\
$(OBJ_DIR)\t04r0101.iso	\
$(OBJ_DIR)\t04r0201.iso	\
$(OBJ_DIR)\t04r0301.iso	\
$(OBJ_DIR)\t04r0401.iso	\
$(OBJ_DIR)\t04r0501.iso	\
$(OBJ_DIR)\t04r0601.iso	\
$(OBJ_DIR)\t04r0701.iso	\
$(OBJ_DIR)\t04r0801.iso	\
$(OBJ_DIR)\t05r0101.iso	\
$(OBJ_DIR)\t05r0201.iso	\
$(OBJ_DIR)\t05r0202.iso	\
$(OBJ_DIR)\t05r0203.iso	\
$(OBJ_DIR)\t05r0204.iso	\
$(OBJ_DIR)\t05r0205.iso	\
$(OBJ_DIR)\t05r0206.iso	\
$(OBJ_DIR)\t05r0207.iso	\
$(OBJ_DIR)\t05r0301.iso	\
$(OBJ_DIR)\t05r0401.iso	\
$(OBJ_DIR)\t05r0501.iso	\
$(OBJ_DIR)\t05r0601.iso	\
$(OBJ_DIR)\t06r0101.iso	\
$(OBJ_DIR)\t06r0201.iso	\
$(OBJ_DIR)\t06r0301.iso	\
$(OBJ_DIR)\t06r0401.iso	\
$(OBJ_DIR)\t06r0501.iso	\
$(OBJ_DIR)\t06r0601.iso	\
$(OBJ_DIR)\t06r0701.iso	\
$(OBJ_DIR)\t06r0801.iso	\
$(OBJ_DIR)\t07r0101.iso	\
$(OBJ_DIR)\t07r0102.iso	\
$(OBJ_DIR)\t07r0103.iso	\
$(OBJ_DIR)\t07r0104.iso	\
$(OBJ_DIR)\t07r0105.iso	\
$(OBJ_DIR)\t07r0106.iso	\
$(OBJ_DIR)\t07r0201.iso	\
$(OBJ_DIR)\t07r0202.iso	\
$(OBJ_DIR)\t07r0203.iso	\
$(OBJ_DIR)\t07r0204.iso	\
$(OBJ_DIR)\t07r0205.iso	\
$(OBJ_DIR)\t07r0301.iso	\
$(OBJ_DIR)\t07r0401.iso	\
$(OBJ_DIR)\t07r0501.iso	\
$(OBJ_DIR)\t07r0601.iso	\
$(OBJ_DIR)\t07r0701.iso	\
$(OBJ_DIR)\t07r0801.iso	\
$(OBJ_DIR)\t07r0901.iso	\
$(OBJ_DIR)\t07r1001.iso	\
$(OBJ_DIR)\t08r0101.iso	\
$(OBJ_DIR)\t08r0201.iso	\
$(OBJ_DIR)\t08r0301.iso	\
$(OBJ_DIR)\t08r0401.iso	\
$(OBJ_DIR)\t08r0501.iso	\
$(OBJ_DIR)\t08r0601.iso	\
$(OBJ_DIR)\t08r0701.iso	\
$(OBJ_DIR)\t08r0801.iso	\
$(OBJ_DIR)\t09r0101.iso	\
$(OBJ_DIR)\t09r0201.iso	\
$(OBJ_DIR)\t09r0301.iso	\
$(OBJ_DIR)\t09r0302.iso	\
$(OBJ_DIR)\t09r0303.iso	\
$(OBJ_DIR)\t09r0304.iso	\
$(OBJ_DIR)\t09r0401.iso	\
$(OBJ_DIR)\t09r0501.iso	\
$(OBJ_DIR)\t10r0101.iso	\
$(OBJ_DIR)\t11r0101.iso	\
$(OBJ_DIR)\t11r0102.iso	\
$(OBJ_DIR)\t11r0201.iso	\
$(OBJ_DIR)\t11r0301.iso	\
$(OBJ_DIR)\t11r0401.iso	\
$(OBJ_DIR)\t11r0501.iso	\
$(OBJ_DIR)\t11r0601.iso	\
$(OBJ_DIR)\t11r0701.iso	\
$(OBJ_DIR)\t11r0801.iso	\
$(OBJ_DIR)\r02r0101.iso	\
$(OBJ_DIR)\r02r0201.iso	\
$(OBJ_DIR)\r02r0301.iso	\
$(OBJ_DIR)\r02r0401.iso	\
$(OBJ_DIR)\r02r0501.iso	\
$(OBJ_DIR)\r04r0101.iso	\
$(OBJ_DIR)\r05r0101.iso	\
$(OBJ_DIR)\r05r0201.iso	\
$(OBJ_DIR)\r05r0301.iso	\
$(OBJ_DIR)\r06r0101.iso	\
$(OBJ_DIR)\r06r0201.iso	\
$(OBJ_DIR)\r07r0101.iso	\
$(OBJ_DIR)\r07r0201.iso	\
$(OBJ_DIR)\r07r0301.iso	\
$(OBJ_DIR)\r08r0101.iso	\
$(OBJ_DIR)\r08r0201.iso	\
$(OBJ_DIR)\r10r0101.iso	\
$(OBJ_DIR)\r10r0201.iso	\
$(OBJ_DIR)\r10r0301.iso	\
$(OBJ_DIR)\r11r0101.iso	\
$(OBJ_DIR)\r11r0102.iso	\
$(OBJ_DIR)\r11r0201.iso	\
$(OBJ_DIR)\r12r0101.iso	\
$(OBJ_DIR)\r12r0102.iso	\
$(OBJ_DIR)\r12r0201.iso	\
$(OBJ_DIR)\r15r0101.iso	\
$(OBJ_DIR)\r15r0102.iso	\
$(OBJ_DIR)\r16r0101.iso	\
$(OBJ_DIR)\r16r0102.iso	\
$(OBJ_DIR)\r16r0201.iso	\
$(OBJ_DIR)\r18r0101.iso	\
$(OBJ_DIR)\r18r0102.iso	\
$(OBJ_DIR)\r20r0101.iso	\
$(OBJ_DIR)\r23r0101.iso	\
$(OBJ_DIR)\r22r0101.iso	\
$(OBJ_DIR)\r25r0101.iso	\
$(OBJ_DIR)\d01r0101.iso	\
$(OBJ_DIR)\d02r0101.iso	\
$(OBJ_DIR)\d02r0102.iso	\
$(OBJ_DIR)\d02r0103.iso	\
$(OBJ_DIR)\d03r0101.iso	\
$(OBJ_DIR)\d03r0102.iso	\
$(OBJ_DIR)\d03r0103.iso	\
$(OBJ_DIR)\d03r0104.iso	\
$(OBJ_DIR)\d03r0105.iso	\
$(OBJ_DIR)\d03r0106.iso	\
$(OBJ_DIR)\d03r0107.iso	\
$(OBJ_DIR)\d03r0108.iso	\
$(OBJ_DIR)\d03r0109.iso	\
$(OBJ_DIR)\d03r0110.iso	\
$(OBJ_DIR)\d04r0101.iso	\
$(OBJ_DIR)\d06r0101.iso	\
$(OBJ_DIR)\d07r0101.iso	\
$(OBJ_DIR)\d08r0101.iso	\
$(OBJ_DIR)\d09r0101.iso	\
$(OBJ_DIR)\d09r0102.iso	\
$(OBJ_DIR)\d09r0103.iso	\
$(OBJ_DIR)\d09r0104.iso	\
$(OBJ_DIR)\d09r0105.iso	\
$(OBJ_DIR)\d10r0101.iso	\
$(OBJ_DIR)\d10r0102.iso	\
$(OBJ_DIR)\d10r0103.iso	\
$(OBJ_DIR)\d10r0104.iso	\
$(OBJ_DIR)\d10r0105.iso	\
$(OBJ_DIR)\d10r0106.iso	\
$(OBJ_DIR)\d10r0107.iso	\
$(OBJ_DIR)\d10r0108.iso	\
$(OBJ_DIR)\d10r0109.iso	\
$(OBJ_DIR)\d10r0110.iso	\
$(OBJ_DIR)\d10r0111.iso	\
$(OBJ_DIR)\d11r0101.iso	\
$(OBJ_DIR)\d11r0102.iso	\
$(OBJ_DIR)\d11r0103.iso	\
$(OBJ_DIR)\d12r0101.iso	\
$(OBJ_DIR)\d12r0102.iso	\
$(OBJ_DIR)\d12r0103.iso	\
$(OBJ_DIR)\d12r0104.iso	\
$(OBJ_DIR)\d12r0105.iso	\
$(OBJ_DIR)\d12r0106.iso	\
$(OBJ_DIR)\d12r0107.iso	\
$(OBJ_DIR)\d12r0108.iso	\
$(OBJ_DIR)\d12r0109.iso	\
$(OBJ_DIR)\d13r0101.iso	\
$(OBJ_DIR)\d13r0102.iso	\
$(OBJ_DIR)\d14r0104.iso	\
$(OBJ_DIR)\d14r0109.iso	\
$(OBJ_DIR)\d14r0114.iso	\
$(OBJ_DIR)\d14r0115.iso	\
$(OBJ_DIR)\d14r0116.iso	\
$(OBJ_DIR)\d14r0117.iso	\
$(OBJ_DIR)\d14r0118.iso	\
$(OBJ_DIR)\d15r0101.iso	\
$(OBJ_DIR)\d16r0101.iso	\
$(OBJ_DIR)\d16r0102.iso	\
$(OBJ_DIR)\d16r0103.iso	\
$(OBJ_DIR)\d16r0104.iso	\
$(OBJ_DIR)\effect.iso	\
$(OBJ_DIR)\c_effect.iso	\
$(OBJ_DIR)\eff_tbl.iso	\
$(OBJ_DIR)\fighter.iso	\
$(OBJ_DIR)\setdmons.iso	\
$(OBJ_DIR)\d_action.iso	\
$(OBJ_DIR)\useitem2.iso	\
$(OBJ_DIR)\window.iso	\
$(OBJ_DIR)\worldmap.iso	\
$(OBJ_DIR)\demo.iso	\
$(OBJ_DIR)\shinka.iso	\
$(OBJ_DIR)\spattack.iso	\
$(OBJ_DIR)\sgb_col.iso	\
$(OBJ_DIR)\saveload.iso	\
$(OBJ_DIR)\a_demo.iso	\
$(OBJ_DIR)\actsub.iso	\
$(OBJ_DIR)\battle.iso	\
$(OBJ_DIR)\observe.iso	\
$(OBJ_DIR)\tools.iso	\
$(OBJ_DIR)\banktool.iso	\
$(OBJ_DIR)\ev_tool.iso	\
$(OBJ_DIR)\bmusic.iso	\
$(OBJ_DIR)\bmusic2.iso	\
$(OBJ_DIR)\bmusic3.iso	\
$(OBJ_DIR)\m_asa.iso	\
$(OBJ_DIR)\m_chari.iso	\
$(OBJ_DIR)\m_dung.iso	\
$(OBJ_DIR)\m_field1.iso	\
$(OBJ_DIR)\m_field2.iso	\
$(OBJ_DIR)\m_field3.iso	\
$(OBJ_DIR)\m_field4.iso	\
$(OBJ_DIR)\m_field5.iso	\
$(OBJ_DIR)\m_htown.iso	\
$(OBJ_DIR)\m_casino.iso	\
$(OBJ_DIR)\m_kokan1.iso	\
$(OBJ_DIR)\m_kokan2.iso	\
$(OBJ_DIR)\m_title.iso	\
$(OBJ_DIR)\m_town1.iso	\
$(OBJ_DIR)\m_fan1.iso	\
$(OBJ_DIR)\m_fan2.iso	\
$(OBJ_DIR)\m_dung2.iso	\
$(OBJ_DIR)\m_awalk.iso	\
$(OBJ_DIR)\m_ohkido.iso	\
$(OBJ_DIR)\m_fight1.iso	\
$(OBJ_DIR)\m_fight3.iso	\
$(OBJ_DIR)\m_fight4.iso	\
$(OBJ_DIR)\m_fight5.iso	\
$(OBJ_DIR)\m_dung3.iso	\
$(OBJ_DIR)\m_dung4.iso	\
$(OBJ_DIR)\m_rival.iso	\
$(OBJ_DIR)\m_fan3.iso	\
$(OBJ_DIR)\m_fan4.iso	\
$(OBJ_DIR)\m_fan5.iso	\
$(OBJ_DIR)\m_fan6.iso	\
$(OBJ_DIR)\m_fan8.iso	\
$(OBJ_DIR)\m_santo.iso	\
$(OBJ_DIR)\m_town2.iso	\
$(OBJ_DIR)\m_town3.iso	\
$(OBJ_DIR)\m_town4.iso	\
$(OBJ_DIR)\m_town5.iso	\
$(OBJ_DIR)\m_town6.iso	\
$(OBJ_DIR)\m_labo.iso	\
$(OBJ_DIR)\m_tou1.iso	\
$(OBJ_DIR)\m_tou2.iso	\
$(OBJ_DIR)\m_deal1.iso	\
$(OBJ_DIR)\m_deal2.iso	\
$(OBJ_DIR)\m_deal3.iso	\
$(OBJ_DIR)\m_start.iso	\
$(OBJ_DIR)\m_sea.iso	\
$(OBJ_DIR)\m_vic1.iso	\
$(OBJ_DIR)\m_vic2.iso	\
$(OBJ_DIR)\m_vic3.iso	\
$(OBJ_DIR)\m_purin.iso	\
$(OBJ_DIR)\m_shinka.iso	\
$(OBJ_DIR)\m_gym.iso	\
$(OBJ_DIR)\m_pmc.iso	\
$(OBJ_DIR)\m_dendou.iso	\
$(OBJ_DIR)\m_ending.iso	\
$(OBJ_DIR)\i_msg2_0.iso	\
$(OBJ_DIR)\i_msg2_1.iso	\
$(OBJ_DIR)\i_msg2_2.iso	\
$(OBJ_DIR)\i_msg2_3.iso	\
$(OBJ_DIR)\i_msg2_4.iso	\
$(OBJ_DIR)\i_msg2_5.iso	\
$(OBJ_DIR)\i_msg2_6.iso	\
$(OBJ_DIR)\i_msg2_7.iso	\
$(OBJ_DIR)\i_msg2_8.iso	\
$(OBJ_DIR)\i_msg2_9.iso	\
$(OBJ_DIR)\i_msg2_a.iso	\
$(OBJ_DIR)\pmcom.iso


TARGET = $(OBJ_DIR)\bluemons.isx


normal:setdir checkdir $(TARGET) resetdir

all:setdir checkdir deleteiso $(TARGET) resetdir


#
#
.def{$(OBJ_DIR)}.iso:
	copy $< $(<:.def=.dmg)
	copy $< $(TMP_DIR)\$(<:.def=.dmg)
	echo $(<:.def= )
	$(MASM) $(<:.def= )
	copy $(<:.def=.iso) $(OBJ_DIR)
	del $(<:.def=.iso)
	del $(<:.def=.dmg)


.dmg{$(OBJ_DIR)}.iso:
	echo $(<:.dmg= )
	$(MASM) $(<:.dmg= )
	copy $(<:.dmg=.iso) $(OBJ_DIR)
	del $(<:.dmg=.iso)


#
#
$(TARGET):$(OBJS)
	$(LINK) @<<$(LINKFILE)
$(LFLAGS)
$(OBJS:	=+^
)
,$(TARGET)
<<KEEP


#
#
checkdir:
	if not exist $(OBJ_DIR)\nul md $(OBJ_DIR)
	if not exist $(TMP_DIR)\nul md $(TMP_DIR)

setdir:
	cd $(SRC_DIR)

resetdir:
	cd ..

deleteiso:
	del $(OBJ_DIR)\*.iso
	del $(OBJ_DIR)\*.isx


#################################
#                               #
# 依存関係リストのインクルード	#
#                               #
#################################
!include "depends.mak"

