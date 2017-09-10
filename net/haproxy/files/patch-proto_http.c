
--- src/proto_http.c
+++ src/proto_http.c
@@ -6856,11 +6856,9 @@ int http_process_res_common(struct stream *s, struct channel *rep, int an_bit, s
 	}
 
  skip_header_mangling:
-	if ((msg->flags & HTTP_MSGF_XFER_LEN) || HAS_DATA_FILTERS(s, rep) ||
-	    (txn->flags & TX_CON_WANT_MSK) == TX_CON_WANT_TUN) {
-		rep->analysers &= ~AN_RES_FLT_XFER_DATA;
-		rep->analysers |= AN_RES_HTTP_XFER_BODY;
-	}
+	/* Always enter in the body analyzer */
+	rep->analysers &= ~AN_RES_FLT_XFER_DATA;
+	rep->analysers |= AN_RES_HTTP_XFER_BODY;
 
 	/* if the user wants to log as soon as possible, without counting
 	 * bytes from the server, then this is the right moment. We have
@@ -7003,11 +7001,11 @@ int http_response_forward_body(struct stream *s, struct channel *res, int an_bit
 
 	/* When TE: chunked is used, we need to get there again to parse
 	 * remaining chunks even if the server has closed, so we don't want to
-	 * set CF_DONTCLOSE. Similarly, if the body length is undefined, if
-	 * keep-alive is set on the client side or if there are filters
-	 * registered on the stream, we don't want to forward a close
+	 * set CF_DONTCLOSE. Similarly, if keep-alive is set on the client side
+	 * or if there are filters registered on the stream, we don't want to
+	 * forward a close
 	 */
-	if ((msg->flags & HTTP_MSGF_TE_CHNK) || !(msg->flags & HTTP_MSGF_XFER_LEN) ||
+	if ((msg->flags & HTTP_MSGF_TE_CHNK) ||
 	    HAS_DATA_FILTERS(s, res) ||
 	    (txn->flags & TX_CON_WANT_MSK) == TX_CON_WANT_KAL ||
 	    (txn->flags & TX_CON_WANT_MSK) == TX_CON_WANT_SCL)
@@ -7024,6 +7022,14 @@ int http_response_forward_body(struct stream *s, struct channel *res, int an_bit
 	if ((msg->flags & HTTP_MSGF_TE_CHNK) || (msg->flags & HTTP_MSGF_COMPRESSING))
 		res->flags |= CF_EXPECT_MORE;
 
+	/* If there is neither content-length, nor transfer-encoding header
+	 * _AND_ there is no data filtering, we can safely forward all data
+	 * indefinitely. */
+	if (!(msg->flags & HTTP_MSGF_XFER_LEN) && !HAS_DATA_FILTERS(s, res)) {
+		buffer_flush(res->buf);
+		channel_forward_forever(res);
+	}
+
 	/* the stream handler will take care of timeouts and errors */
 	return 0;
