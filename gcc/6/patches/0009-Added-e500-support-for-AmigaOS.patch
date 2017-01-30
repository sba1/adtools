From e4c6c0e05575c8aab06e5d2a16ac183f83206cbc Mon Sep 17 00:00:00 2001
From: Sebastian Bauer <mail@sebastianbauer.info>
Date: Mon, 30 Jan 2017 20:49:17 +0100
Subject: [PATCH 9/9] Added e500 support for AmigaOS.

---
 gcc/config.gcc | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

diff --git a/gcc/config.gcc b/gcc/config.gcc
index d262672083d57bd77846ba9277aeb3ef5279d11e..3699a9831cccbb6a74ed0f8b2ddf5574bee1f086 100644
--- a/gcc/config.gcc
+++ b/gcc/config.gcc
@@ -2295,13 +2295,13 @@ nvptx-*)
 	;;
 pdp11-*-*)
 	tm_file="${tm_file} newlib-stdint.h"
 	use_gcc_stdint=wrap
 	;;
 powerpc-*-amigaos*)
-	tm_file="${tm_file} dbxelf.h elfos.h rs6000/sysv4.h rs6000/amigaos.h"
+	tm_file="${tm_file} dbxelf.h elfos.h rs6000/sysv4.h rs6000/amigaos.h rs6000/e500.h"
 	tm_p_file="${tm_p_file} rs6000/amigaos-protos.h"
 	extra_options="${extra_options} rs6000/sysv4.opt rs6000/amigaos.opt"
 	tmake_file="rs6000/t-amigaos"
 	extra_objs=amigaos.o
 	use_collect2=no
 	;;
-- 
1.9.1

