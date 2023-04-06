/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished  proprietary information of BroadOn Communications Corp.,
 *  and  are protected by Federal copyright law. They may not be disclosed
 *  to  third  parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 */
#ifndef __EDITLINE_H__
#define __EDITLINE_H__

#include <histedit.h>
extern const char *editline_inl;
extern int editline_count;
extern void setup_editline(const char *prog);
extern void delete_editline(void);
extern const char *editline_inl;
extern int editline_count;
extern EditLine *el;
extern History *hs;
extern HistEvent ev;
extern Tokenizer *tok;
#endif /* __EDITLINE_H__ */
