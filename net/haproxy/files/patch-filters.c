--- src/filters.c
+++ src/filters.c
@@ -861,12 +861,7 @@ flt_end_analyze(struct stream *s, struct channel *chn, unsigned int an_bit)
 		/* Remove backend filters from the list */
 		flt_stream_release(s, 1);
 	}
-	else {
-		/* This analyzer ends only for one channel. So wake up the
-		 * stream to be sure to process it for the other side as soon as
-		 * possible. */
-		task_wakeup(s->task, TASK_WOKEN_MSG);
-	}
+
 	return ret;
 }
 
