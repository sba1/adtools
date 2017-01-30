From 2b3f8d96dd38b95816ee32ab6e7564b4cf9001dd Mon Sep 17 00:00:00 2001
From: Sebastian Bauer <mail@sebastianbauer.info>
Date: Sat, 5 Dec 2015 13:17:26 +0100
Subject: [PATCH 6/9] Expand arg zero on AmigaOS using the PROGDIR: assign.

This should make sure that the proper relative paths are computed during
process_command().
---
 gcc/gcc.c | 10 ++++++++++
 1 file changed, 10 insertions(+)

diff --git a/gcc/gcc.c b/gcc/gcc.c
index eb56ea7242ab51c941b88d72f8dee2a0381e2c8f..4184cf1f3ac8063f9ae8f4b76da1e5e33c6f76cd 100644
--- a/gcc/gcc.c
+++ b/gcc/gcc.c
@@ -7166,12 +7166,22 @@ driver::~driver ()
 int
 driver::main (int argc, char **argv)
 {
   bool early_exit;
 
   set_progname (argv[0]);
+#ifdef __amigaos4__
+  /* Expand the command name on AmigaOS */
+  char *expanded_progdir = lrealpath("/progdir/");
+  if (expanded_progdir)
+    {
+      char *expanded_argv0 = concat(expanded_progdir,"/",progname,NULL);
+      argv[0] = expanded_argv0; /* FIXME: Leak */
+      free(expanded_progdir);
+    }
+#endif
   expand_at_files (&argc, &argv);
   decode_argv (argc, const_cast <const char **> (argv));
   global_initializations ();
   build_multilib_strings ();
   set_up_specs ();
   putenv_COLLECT_GCC (argv[0]);
-- 
1.9.1

