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

/* Stuff to use editline, the BSD-licensed readline clone */
#include <histedit.h>

const char *editline_inl;
int editline_count;
EditLine *el = NULL;
History *hs = NULL;
HistEvent ev;
Tokenizer *tok;

char *
prompt(EditLine *el) { return ">"; }

void
setup_editline(const char *prog)
{
  el = el_init(prog, stdin, stdout, stderr);
  hs = history_init();
  tok = tok_init(NULL);
  history(hs, &ev, H_SETSIZE, 800);
  el_set(el, EL_PROMPT, prompt);
  el_set(el, EL_EDITOR, "emacs");
  el_set(el, EL_HIST, history, hs);
  return;
}

void
delete_editline()
{
  if (el) el_end(el);
  if (hs) history_end(hs);
  if (tok) tok_end(tok);
  return;
}
