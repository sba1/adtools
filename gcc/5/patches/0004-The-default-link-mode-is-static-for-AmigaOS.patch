From 8eb1aa062283f82007d639e862278a750f314da5 Mon Sep 17 00:00:00 2001
From: Sebastian Bauer <mail@sebastianbauer.info>
Date: Wed, 2 Dec 2015 20:56:33 +0100
Subject: [PATCH 4/6] The default link mode is static for AmigaOS.

Changed the g++ driver to reflect this.
---
 gcc/cp/g++spec.c | 8 ++++++--
 1 file changed, 6 insertions(+), 2 deletions(-)

diff --git a/gcc/cp/g++spec.c b/gcc/cp/g++spec.c
index 6536d7e776f861b4bd40277e96c80a635cbcc85e..ff1d77eaefc20039f7e5df48ffb849ee533b9797 100644
--- a/gcc/cp/g++spec.c
+++ b/gcc/cp/g++spec.c
@@ -102,14 +102,14 @@ lang_specific_driver (struct cl_decoded_option **in_decoded_options,
   /* By default, we throw on the math library if we have one.  */
   int need_math = (MATH_LIBRARY[0] != '\0');
 
   /* By default, we throw on the time library if we have one.  */
   int need_time = (TIME_LIBRARY[0] != '\0');
 
-  /* True if we saw -static.  */
-  int static_link = 0;
+  /* False if we saw -shared.  */
+  int static_link = 1;
 
   /* True if we should add -shared-libgcc to the command-line.  */
   int shared_libgcc = 1;
 
   /* The total number of arguments with the new stuff.  */
   unsigned int argc;
@@ -196,12 +196,16 @@ lang_specific_driver (struct cl_decoded_option **in_decoded_options,
 	  break;
 
 	case OPT_static:
 	  static_link = 1;
 	  break;
 
+	case OPT_shared:
+	  static_link = 0;
+	  break;
+
 	case OPT_static_libgcc:
 	  shared_libgcc = 0;
 	  break;
 
 	case OPT_static_libstdc__:
 	  library = library >= 0 ? 2 : library;
-- 
2.1.4

