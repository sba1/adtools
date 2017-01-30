From 0f8e76ecc9220e1d4e1f311a52a5e80bd4ad8bb8 Mon Sep 17 00:00:00 2001
From: Sebastian Bauer <mail@sebastianbauer.info>
Date: Thu, 9 Jul 2015 06:54:37 +0200
Subject: [PATCH 3/9] Disable .machine directive generation.

It breaks manual args to the assembler with different flavor,
e.g., -Wa,-m440. This is probably not the right fix.

This reverts parts of a commit from 2015-03-03.
---
 gcc/config/rs6000/rs6000.c | 3 +++
 1 file changed, 3 insertions(+)

diff --git a/gcc/config/rs6000/rs6000.c b/gcc/config/rs6000/rs6000.c
index cd79b2034b59168b07c84dd6bf32faaf4a648cd0..14b40fe386382a6b418176084c57ec8db73b4280 100644
--- a/gcc/config/rs6000/rs6000.c
+++ b/gcc/config/rs6000/rs6000.c
@@ -5689,12 +5689,14 @@ rs6000_file_start (void)
     }
 
 #ifdef USING_ELFOS_H
   if (rs6000_default_cpu == 0 || rs6000_default_cpu[0] == '\0'
       || !global_options_set.x_rs6000_cpu_index)
     {
+      /* Temporarily disabled as it overrides e.g., -mcpu=440 */
+#if 0
       fputs ("\t.machine ", asm_out_file);
       if ((rs6000_isa_flags & OPTION_MASK_MODULO) != 0)
 	fputs ("power9\n", asm_out_file);
       else if ((rs6000_isa_flags & OPTION_MASK_DIRECT_MOVE) != 0)
 	fputs ("power8\n", asm_out_file);
       else if ((rs6000_isa_flags & OPTION_MASK_POPCNTD) != 0)
@@ -5706,12 +5708,13 @@ rs6000_file_start (void)
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
 }
-- 
1.9.1

