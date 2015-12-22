From 85c5321c36040abb1c3b70cb1e0f9bf217178957 Mon Sep 17 00:00:00 2001
From: Sebastian Bauer <mail@sebastianbauer.info>
Date: Sat, 5 Dec 2015 13:17:26 +0100
Subject: [PATCH 6/6] Expand arg zero on AmigaOS using the PROGDIR: assign.

This should make sure that the proper relative paths are computed during
process_command().
---
 gcc/gcc.c | 10 ++++++++++
 1 file changed, 10 insertions(+)

diff --git a/gcc/gcc.c b/gcc/gcc.c
index 8239a6b2152ac192498cd8a50b0d4b9c7db45c62..f6f1ba3195a4ffc8e335d7abe797d4b006fc96d5 100644
--- a/gcc/gcc.c
+++ b/gcc/gcc.c
@@ -6898,12 +6898,22 @@ compare_files (char *cmpfile[])
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
2.1.4

