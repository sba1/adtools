From 43dda55bb84a70181e84f496fd8417ed3c22db54 Mon Sep 17 00:00:00 2001
From: Sebastian Bauer <mail@sebastianbauer.info>
Date: Thu, 9 Jul 2015 06:54:37 +0200
Subject: [PATCH 3/6] Disable .machine directive generation.

It breaks manual args to the assembler with different flavor,
e.g., -Wa,-m440. This is probably not the right fix.

This reverts parts of a commit from 2015-03-03.
---
 gcc/config/rs6000/rs6000.c | 3 +++
 1 file changed, 3 insertions(+)

diff --git a/gcc/config/rs6000/rs6000.c b/gcc/config/rs6000/rs6000.c
index ee0ea2ffabb6b9c6fdcba687d88be1e1164374ee..19544afa364f7f7ab1a5c5a61ad7891218398f99 100644
--- a/gcc/config/rs6000/rs6000.c
+++ b/gcc/config/rs6000/rs6000.c
@@ -5191,12 +5191,14 @@ rs6000_file_start (void)
     }
 
 #ifdef USING_ELFOS_H
   if (rs6000_default_cpu == 0 || rs6000_default_cpu[0] == '\0'
       || !global_options_set.x_rs6000_cpu_index)
     {
+      /* Temporarily disabled as it overrides e.g., -mcpu=440 */
+#if 0
       fputs ("\t.machine ", asm_out_file);
       if ((rs6000_isa_flags & OPTION_MASK_DIRECT_MOVE) != 0)
 	fputs ("power8\n", asm_out_file);
       else if ((rs6000_isa_flags & OPTION_MASK_POPCNTD) != 0)
 	fputs ("power7\n", asm_out_file);
       else if ((rs6000_isa_flags & OPTION_MASK_CMPB) != 0)
@@ -5206,12 +5208,13 @@ rs6000_file_start (void)
       else if ((rs6000_isa_flags & OPTION_MASK_MFCRF) != 0)
 	fputs ("power4\n", asm_out_file);
       else if ((rs6000_isa_flags & OPTION_MASK_POWERPC64) != 0)
 	fputs ("ppc64\n", asm_out_file);
       else
 	fputs ("ppc\n", asm_out_file);
+#endif
     }
 #endif
 
   if (DEFAULT_ABI == ABI_ELFv2)
     fprintf (file, "\t.abiversion 2\n");
 
-- 
2.1.4

