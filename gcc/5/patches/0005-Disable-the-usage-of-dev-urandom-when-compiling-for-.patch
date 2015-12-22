From c9b38a7315faed955e2f01e37f84d06ba32aa9b5 Mon Sep 17 00:00:00 2001
From: Sebastian Bauer <mail@sebastianbauer.info>
Date: Wed, 2 Dec 2015 21:39:42 +0100
Subject: [PATCH 5/6] Disable the usage of /dev/urandom when compiling for
 AmigaOS.

---
 gcc/gcc.c    | 3 +++
 gcc/toplev.c | 4 ++--
 2 files changed, 5 insertions(+), 2 deletions(-)

diff --git a/gcc/gcc.c b/gcc/gcc.c
index d4d061080ba1166fb14069094556246b32265da4..8239a6b2152ac192498cd8a50b0d4b9c7db45c62 100644
--- a/gcc/gcc.c
+++ b/gcc/gcc.c
@@ -9124,22 +9124,25 @@ print_asm_header_spec_function (int arg ATTRIBUTE_UNUSED,
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
index cb6c51739ffc40d19f83efafb02d7670e4da2915..3ba2210c953d2dde2ab919808b86ed3e7a4f4d1e 100644
--- a/gcc/toplev.c
+++ b/gcc/toplev.c
@@ -288,22 +288,22 @@ static void
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
2.1.4

