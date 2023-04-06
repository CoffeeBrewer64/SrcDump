#ifndef __BB_SYSAPP_RL_H_
#define __BB_SYSAPP_RL_H_

#include <PR/bbtypes.h>
#include <PR/bbcert.h>
#include <PR/bbcrl.h>
#include <PR/bbskapi.h>
#include "common.h"
#include "cert.h"

#define SARL_ERR -1

int saRlBundle(u8 *rlFile,u8 *certFile,BbAppLaunchCrls *rls);
                                 
#endif
