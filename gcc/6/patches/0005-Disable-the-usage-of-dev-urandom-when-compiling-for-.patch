From 5e6d152e0100b004ae0400739db545dcfa5f9671 Mon Sep 17 00:00:00 2001
From: Sebastian Bauer <mail@sebastianbauer.info>
Date: Wed, 2 Dec 2015 21:39:42 +0100
Subject: [PATCH 5/9] Disable the usage of /dev/urandom when compiling for
 AmigaOS.

---
 gcc/gcc.c    | 3 +++
 gcc/toplev.c | 4 ++--
 2 files changed, 5 insertions(+), 2 deletions(-)

diff --git a/gcc/gcc.c b/gcc/gcc.c
index e88e6d3497c13a4e9a5d92d71de6128678ec546f..eb56ea7242ab51c941b88d72f8dee2a0381e2c8f 100644
--- a/gcc/gcc.c
+++ b/gcc/gcc.c
@@ -9511,22 +9511,25 @@ print_asm_header_spec_function (int arg ATTRIBUTE_UNUSED,
 /* Get a random number for -frandom-seed */
 
 static unsigned HOST_WIDE_INT
 get_random_number (void)
 {
   unsigned HOST_WIDE_INT ret = 0;
+
+#ifndef __amigaos4__
   int fd; 
 
   fd = open ("/dev/urandom", O_RDONLY); 
   if (fd >= 0)
     {
       read (fd, &ret, sizeof (HOST_WIDE_INT));
       close (fd);
       if (ret)
         return ret;
     }
+#endif
 
   /* Get some more or less random data.  */
 #ifdef HAVE_GETTIMEOFDAY
   {
     struct timeval tv;
 
diff --git a/gcc/toplev.c b/gcc/toplev.c
index 8979d2634260b1e5ad1183ed26da444c47cd3631..de6cdfc5dfdadbef3851fa842d6566648720ffa7 100644
--- a/gcc/toplev.c
+++ b/gcc/toplev.c
@@ -238,22 +238,22 @@ static void
 init_local_tick (void)
 {
   if (!flag_random_seed)
     {
       /* Try urandom first. Time of day is too likely to collide. 
 	 In case of any error we just use the local tick. */
-
+#ifndef __amigaos4__
       int fd = open ("/dev/urandom", O_RDONLY);
       if (fd >= 0)
         {
           if (read (fd, &random_seed, sizeof (random_seed))
               != sizeof (random_seed))
             random_seed = 0;
           close (fd);
         }
-
+#endif
       /* Now get the tick anyways  */
 #ifdef HAVE_GETTIMEOFDAY
       {
 	struct timeval tv;
 
 	gettimeofday (&tv, NULL);
-- 
1.9.1

