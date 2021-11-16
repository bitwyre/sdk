package com.bitwyre.scala_sdk

import java.net.http.HttpClient
import java.time.Duration
import java.time.Instant
import java.io.UnsupportedEncodingException
import java.security.InvalidKeyException
import java.security.MessageDigest
import java.security.NoSuchAlgorithmException
import javax.crypto.Mac
import javax.crypto.spec.SecretKeySpec
import java.io.IOException
import java.net.URI
import java.net.http.HttpRequest
import java.net.http.HttpResponse
import java.net.URLEncoder
import java.util
import com.bitwyre.scala_sdk.Config

class PrivateAPI(var secret_key: String, var api_key: String) {
    val config = new Config()
    val httpClient = HttpClient.newBuilder
        .version(HttpClient.Version.HTTP_1_1)
        .connectTimeout(Duration.ofSeconds(config.baseURL.TIMEOUT))
        .build

    def getNonce: String = {
        val instant = Instant.now
        val secondsSinceEpoch = instant.getEpochSecond
        val nanoSeconds = instant.getNano
        val nonce = new StringBuilder().append(secondsSinceEpoch).append(nanoSeconds).toString
        nonce
    }

    @throws[NoSuchAlgorithmException]
    @throws[UnsupportedEncodingException]
    def getChecksum(payload: String): String = {
        val md = MessageDigest.getInstance("SHA-256")
        md.update(payload.getBytes("UTF-8"))
        val checksum = md.digest
        val hexString = new StringBuffer
        for (i <- 0 until checksum.length) {
            val hex = Integer.toHexString(0xFF & checksum(i))
            if (hex.length == 1) hexString.append("0")
            hexString.append(hex)
        }
        hexString.toString
    }

    @throws[NoSuchAlgorithmException]
    @throws[UnsupportedEncodingException]
    def getNonceChecksum(nonce: String, checksum: String): String = {
        val temp = new StringBuilder().append(nonce).append(checksum).toString
        val mdgDigest = MessageDigest.getInstance("SHA-256")
        mdgDigest.update(temp.getBytes("UTF-8"))
        val nonce_checksum = mdgDigest.digest
        val hexStr = new StringBuffer
        for (i <- 0 until nonce_checksum.length) {
            val hxa = Integer.toHexString(0xFF & nonce_checksum(i))
            if (hxa.length == 1) hexStr.append("0")
            hexStr.append(hxa)
        }
        hexStr.toString
    }

    @throws[NoSuchAlgorithmException]
    @throws[UnsupportedEncodingException]
    @throws[InvalidKeyException]
    def getSignature(uri_path: String, nonce_checksum: String): String = {
        val data = new StringBuilder().append(uri_path).append(nonce_checksum).toString
        val sha512_HMAC = Mac.getInstance("HmacSHA512")
        val key = new SecretKeySpec(secret_key.getBytes("UTF-8"), "HmacSHA512")
        sha512_HMAC.init(key)
        val hash = sha512_HMAC.doFinal(data.getBytes("UTF-8"))
        val hexSign = new StringBuffer
        for (i <- 0 until hash.length) {
            val hexa = Integer.toHexString(0xFF & hash(i))
            if (hexa.length == 1) hexSign.append("0")
            hexSign.append(hexa)
        }
        hexSign.toString
    }

    @throws[IOException]
    @throws[InterruptedException]
    @throws[NoSuchAlgorithmException]
    @throws[UnsupportedEncodingException]
    @throws[InvalidKeyException]
    def get_account_balance(): Unit = {
        val payload = "\"\\\"\\\"\""
        val priv = new PrivateAPI(secret_key, api_key)
        val nonce = priv.getNonce
        val checksum = priv.getChecksum(payload)
        val nonce_checksum = priv.getNonceChecksum(nonce, checksum)
        val signature = priv.getSignature(config.baseURL.getPrivateAPIEndPoint("ACCOUNT_BALANCE"), nonce_checksum)
        //construct query parameters
        val params = new StringBuilder()
            .append("?nonce=")
            .append(nonce.toLong)
            .append("&checksum=")
            .append(checksum)
            .append("&payload=")
            .append("")
            .toString
        //construct request body
        val request = HttpRequest.newBuilder
            .GET
            .uri(URI.create(config.baseURL.URL_API_BITWYRE + config.baseURL.getPrivateAPIEndPoint("ACCOUNT_BALANCE") + params))
            .setHeader("API-Key", api_key)
            .setHeader("API-Sign", signature)
            .build
        //send request and get response
        val response = httpClient.send(request, HttpResponse.BodyHandlers.ofString)
        // print status code
        println(response.statusCode)
        //print response message
        val status = response.statusCode
        if (status == 200) {
            println("OK")
        }
        // print response body
        println(response.body)
    }

    @throws[IOException]
    @throws[InterruptedException]
    @throws[NoSuchAlgorithmException]
    @throws[UnsupportedEncodingException]
    @throws[InvalidKeyException]
    def get_account_statement(): Unit = {
        val payload = "\"\\\"\\\"\""
        val priv = new PrivateAPI(secret_key, api_key)
        val nonce = priv.getNonce
        val checksum = priv.getChecksum(payload)
        val nonce_checksum = priv.getNonceChecksum(nonce, checksum)
        val signature = priv.getSignature(config.baseURL.getPrivateAPIEndPoint("ACCOUNT_STATEMENT"), nonce_checksum)
        //construct query parameters
        val params = new StringBuilder()
            .append("?nonce=")
            .append(nonce.toLong)
            .append("&checksum=")
            .append(checksum)
            .append("&payload=")
            .append("")
            .toString
        //construct request body
        val request = HttpRequest.newBuilder
            .GET
            .uri(URI.create(config.baseURL.URL_API_BITWYRE + config.baseURL.getPrivateAPIEndPoint("ACCOUNT_STATEMENT") + params))
            .setHeader("API-Key", api_key)
            .setHeader("API-Sign", signature)
            .build
        //send request and get response
        val response = httpClient.send(request, HttpResponse.BodyHandlers.ofString)
        // print status code
        println(response.statusCode)
        //print response message
        val status = response.statusCode
        if (status == 200) println("OK")
        // print response body
        println(response.body)
    }

    @throws[IOException]
    @throws[InterruptedException]
    @throws[NoSuchAlgorithmException]
    @throws[UnsupportedEncodingException]
    @throws[InvalidKeyException]
    def get_transaction_histories(): Unit = {
        val payload = "\"\\\"\\\"\""
        val priv = new PrivateAPI(secret_key, api_key)
        val nonce = priv.getNonce
        val checksum = priv.getChecksum(payload)
        val nonce_checksum = priv.getNonceChecksum(nonce, checksum)
        val signature = priv.getSignature(config.baseURL.getPrivateAPIEndPoint("TRANSACTION_HISTORIES"), nonce_checksum)
        //construct query parameters
        val params = new StringBuilder()
            .append("?nonce=")
            .append(nonce.toLong)
            .append("&checksum=")
            .append(checksum)
            .append("&payload=")
            .append("")
            .toString
        //construct request body
        val request = HttpRequest.newBuilder
            .GET
            .uri(URI.create(config.baseURL.URL_API_BITWYRE + config.baseURL.getPrivateAPIEndPoint("TRANSACTION_HISTORIES") + params))
            .setHeader("API-Key", api_key)
            .setHeader("API-Sign", signature)
            .build
        //send request and get response
        val response = httpClient.send(request, HttpResponse.BodyHandlers.ofString)
        // print status code
        println(response.statusCode)
        //print response message
        val status = response.statusCode
        if (status == 200) println("OK")
        // print response body
        println(response.body)
    }

    @throws[IOException]
    @throws[InterruptedException]
    @throws[NoSuchAlgorithmException]
    @throws[UnsupportedEncodingException]
    @throws[InvalidKeyException]
    def get_open_orders(instrument: String, from_time: Int, to_time: Int): Unit = {
        val payload = "\"\\\"{\\\\\\\"instrument\\\\\\\":\\\\\\\"" + instrument + "\\\\\\\",\\\\\\\"from_time\\\\\\\":" + from_time + ",\\\\\\\"to_time\\\\\\\":" + to_time + "}\\\"\""
        val priv = new PrivateAPI(secret_key, api_key)
        val nonce = priv.getNonce
        val checksum = priv.getChecksum(payload)
        val nonce_checksum = priv.getNonceChecksum(nonce, checksum)
        val signature = priv.getSignature(config.baseURL.getPrivateAPIEndPoint("OPEN_ORDERS"), nonce_checksum)
        val payload2 = "{\"instrument\":" + "\"" + instrument + "\"" + ",\"from_time\":" + from_time + ",\"to_time\":" + to_time + "}"
        val encodedPayload = URLEncoder.encode(payload2, "UTF-8")
        //construct query parameters
        val params = new StringBuilder()
            .append("?nonce=")
            .append(nonce.toLong)
            .append("&checksum=")
            .append(checksum)
            .append("&payload=")
            .append(encodedPayload)
            .toString
        //construct request body
        val request = HttpRequest.newBuilder
            .GET
            .uri(URI.create(config.baseURL.URL_API_BITWYRE + config.baseURL.getPrivateAPIEndPoint("OPEN_ORDERS") + params))
            .setHeader("API-Key", api_key)
            .setHeader("API-Sign", signature)
            .build
        //send request and get response
        val response = httpClient.send(request, HttpResponse.BodyHandlers.ofString)
        // print status code
        println(response.statusCode)
        //print response message
        val status = response.statusCode
        if (status == 200) println("OK")
        // print response body
        println(response.body)
    }

    @throws[IOException]
    @throws[InterruptedException]
    @throws[NoSuchAlgorithmException]
    @throws[UnsupportedEncodingException]
    @throws[InvalidKeyException]
    def get_closed_orders(instrument: String, from_time: Int, to_time: Int): Unit = {
        val payload = "\"\\\"{\\\\\\\"instrument\\\\\\\":\\\\\\\"" + instrument + "\\\\\\\",\\\\\\\"from_time\\\\\\\":" + from_time + ",\\\\\\\"to_time\\\\\\\":" + to_time + "}\\\"\""
        val priv = new PrivateAPI(secret_key, api_key)
        val nonce = priv.getNonce
        val checksum = priv.getChecksum(payload)
        val nonce_checksum = priv.getNonceChecksum(nonce, checksum)
        val signature = priv.getSignature(config.baseURL.getPrivateAPIEndPoint("CLOSED_ORDERS"), nonce_checksum)
        val payload2 = "{\"instrument\":" + "\"" + instrument + "\"" + ",\"from_time\":" + from_time + ",\"to_time\":" + to_time + "}"
        val encodedPayload = URLEncoder.encode(payload2, "UTF-8")
        //construct query parameters
        val params = new StringBuilder()
            .append("?nonce=")
            .append(nonce.toLong)
            .append("&checksum=")
            .append(checksum)
            .append("&payload=")
            .append(encodedPayload)
            .toString
        //construct request body
        val request = HttpRequest.newBuilder
            .GET
            .uri(URI.create(config.baseURL.URL_API_BITWYRE + config.baseURL.getPrivateAPIEndPoint("CLOSED_ORDERS") + params))
            .setHeader("API-Key", api_key)
            .setHeader("API-Sign", signature)
            .build
        //send request and get response
        val response = httpClient.send(request, HttpResponse.BodyHandlers.ofString)
        // print status code
        println(response.statusCode)
        //print response message
        val status = response.statusCode
        if (status == 200) println("OK")
        // print response body
        println(response.body)
    }

    @throws[IOException]
    @throws[InterruptedException]
    @throws[NoSuchAlgorithmException]
    @throws[UnsupportedEncodingException]
    @throws[InvalidKeyException]
    def get_order_info(order_id: String): Unit = {
        val payload = "\"\\\"\\\"\""
        val priv = new PrivateAPI(secret_key, api_key)
        val nonce = priv.getNonce
        val checksum = priv.getChecksum(payload)
        val nonce_checksum = priv.getNonceChecksum(nonce, checksum)
        val signature = priv.getSignature(config.baseURL.getPrivateAPIEndPoint("ORDER_INFO") + "/" + order_id, nonce_checksum)
        //construct query parameters
        val params = new StringBuilder()
            .append("?nonce=")
            .append(nonce.toLong)
            .append("&checksum=")
            .append(checksum)
            .append("&payload=")
            .append("")
            .toString
        //construct request body
        val request = HttpRequest.newBuilder
            .GET
            .uri(URI.create(config.baseURL.URL_API_BITWYRE + config.baseURL.getPrivateAPIEndPoint("ORDER_INFO") + "/" + order_id + params))
            .setHeader("API-Key", api_key)
            .setHeader("API-Sign", signature)
            .build
        //send request and get response
        val response = httpClient.send(request, HttpResponse.BodyHandlers.ofString)
        // print status code
        println(response.statusCode)
        //print response message
        val status = response.statusCode
        if (status == 200) println("OK")
        // print response body
        println(response.body)
    }

    @throws[IOException]
    @throws[InterruptedException]
    @throws[NoSuchAlgorithmException]
    @throws[UnsupportedEncodingException]
    @throws[InvalidKeyException]
    def get_trade_history(instrument: String, count: Int, from_time: Int, to_time: Int): Unit = {
        val payload = "\"\\\"{\\\\\\\"instrument\\\\\\\":\\\\\\\"" + instrument + "\\\\\\\",\\\\\\\"count\\\\\\\":" + count + ",\\\\\\\"from_time\\\\\\\":" + from_time + ",\\\\\\\"to_time\\\\\\\":" + to_time + "}\\\"\""
        val priv = new PrivateAPI(secret_key, api_key)
        val nonce = priv.getNonce
        val checksum = priv.getChecksum(payload)
        val nonce_checksum = priv.getNonceChecksum(nonce, checksum)
        val signature = priv.getSignature(config.baseURL.getPrivateAPIEndPoint("TRADE_HISTORY"), nonce_checksum)
        val payload2 = "{\"instrument\":" + "\"" + instrument + "\"" + ",\"count\":" + count + ",\"from_time\":" + from_time + ",\"to_time\":" + to_time + "}"
        val encodedPayload = URLEncoder.encode(payload2, "UTF-8")
        //construct query parameters
        val params = new StringBuilder()
            .append("?nonce=")
            .append(nonce.toLong)
            .append("&checksum=")
            .append(checksum)
            .append("&payload=")
            .append(encodedPayload)
            .toString
        //construct request body
        val request = HttpRequest.newBuilder
            .GET
            .uri(URI.create(config.baseURL.URL_API_BITWYRE + config.baseURL.getPrivateAPIEndPoint("TRADE_HISTORY") + params))
            .setHeader("API-Key", api_key)
            .setHeader("API-Sign", signature)
            .build
        //send request and get response
        val response = httpClient.send(request, HttpResponse.BodyHandlers.ofString)
        // print status code
        println(response.statusCode)
        //print response message
        val status = response.statusCode
        if (status == 200) println("OK")
        // print response body
        println(response.body)
    }

    @throws[IOException]
    @throws[InterruptedException]
    @throws[NoSuchAlgorithmException]
    @throws[UnsupportedEncodingException]
    @throws[InvalidKeyException]
    def opening_new_order(instrument: String, side: Int, price: String, ordtype: Int, orderqty: String): Unit = {
        val payload = "\"\\\"{\\\\\\\"instrument\\\\\\\":\\\\\\\"" + instrument + "\\\\\\\",\\\\\\\"side\\\\\\\":" + side + ",\\\\\\\"price\\\\\\\":\\\\\\\"" + price + "\\\\\\\",\\\\\\\"ordtype\\\\\\\":" + ordtype + ",\\\\\\\"orderqty\\\\\\\":\\\\\\\"" + orderqty + "\\\\\\\"}\\\"\""
        val priv = new PrivateAPI(secret_key, api_key)
        val nonce = priv.getNonce
        val checksum = priv.getChecksum(payload)
        val nonce_checksum = priv.getNonceChecksum(nonce, checksum)
        val signature = priv.getSignature(config.baseURL.getPrivateAPIEndPoint("ORDER"), nonce_checksum)
        val payload2 = "{\\\"instrument\\\":" + "\\\"" + instrument + "\\\"" + ",\\\"side\\\":" + side + ",\\\"price\\\":" + "\\\"" + price + "\\\"" + ",\\\"ordtype\\\":" + ordtype + ",\\\"orderqty\\\":" + "\\\"" + orderqty + "\\\"" + "}"
        //construct query parameters
        val data = new StringBuilder()
            .append("{")
            .append("\"nonce\":")
            .append(nonce.toLong)
            .append(",\"checksum\":")
            .append("\"")
            .append(checksum)
            .append("\"")
            .append(",\"payload\":")
            .append("\"")
            .append(payload2)
            .append("\"")
            .append("}")
            .toString
        //construct request body
        val request = HttpRequest.newBuilder
            .POST(HttpRequest.BodyPublishers.ofString(data))
            .uri(URI.create(config.baseURL.URL_API_BITWYRE + config.baseURL.getPrivateAPIEndPoint("ORDER")))
            .setHeader("API-Key", api_key)
            .setHeader("API-Sign", signature)
            .setHeader("Content-Type", "application/json")
            .build
        //send request and get response
        val response = httpClient.send(request, HttpResponse.BodyHandlers.ofString)
        // print status code
        println(response.statusCode)
        //print response message
        val status = response.statusCode
        if (status == 200) println("OK")
        // print response body
        println(response.body)
    }

    @throws[IOException]
    @throws[InterruptedException]
    @throws[NoSuchAlgorithmException]
    @throws[UnsupportedEncodingException]
    @throws[InvalidKeyException]
    def cancelling_open_order(order_ids: Array[String], qtys: Array[Integer]): Unit = { //Converting Array to List
        val list = new util.ArrayList[String]
        for (id <- order_ids) {
            list.add(id)
        }
        val list2 = new util.ArrayList[Integer]
        for (qty <- qtys) {
            list2.add(qty)
        }
        var j = 0
        var orderids = ""
        for (i <- 0 until order_ids.length) {
            j = i + 1
            orderids = orderids + "\\\\\\\"" + order_ids(i) + "\\\\\\\""
            if (j != order_ids.length) orderids = orderids + ","
        }
        var k = 0
        var temp = ""
        for (i <- 0 until qtys.length) {
            k = i + 1
            temp = temp + qtys(i)
            if (k != qtys.length) temp = temp + ","
        }
        val payload = "\"\\\"{\\\\\\\"order_ids\\\\\\\":[" + orderids + "],\\\\\\\"qtys\\\\\\\":[" + temp + "]}\\\"\""
        val priv = new PrivateAPI(secret_key, api_key)
        val nonce = priv.getNonce
        val checksum = priv.getChecksum(payload)
        val nonce_checksum = priv.getNonceChecksum(nonce, checksum)
        val signature = priv.getSignature(config.baseURL.getPrivateAPIEndPoint("CANCEL_ORDER"), nonce_checksum)
        var l = 0
        var orderids2 = ""
        for (i <- 0 until order_ids.length) {
            l = i + 1
            orderids2 = orderids2 + "\"" + order_ids(i) + "\""
            if (l != order_ids.length) orderids2 = orderids2 + ","
        }
        var m = 0
        var temp2 = ""
        for (i <- 0 until qtys.length) {
            m = i + 1
            temp2 = temp2 + qtys(i)
            if (m != qtys.length) temp2 = temp2 + ","
        }
        val payload2 = "{\"order_ids\":[" + orderids2 + "],\"qtys\":[" + temp2 + "]}"
        val encodedPayload = URLEncoder.encode(payload2, "UTF-8")
        //construct query parameters
        val params = new StringBuilder()
            .append("?nonce=")
            .append(nonce.toLong)
            .append("&checksum=")
            .append(checksum)
            .append("&payload=")
            .append(encodedPayload)
            .toString
        //construct request body
        val request = HttpRequest.newBuilder
            .DELETE
            .uri(URI.create(config.baseURL.URL_API_BITWYRE + config.baseURL.getPrivateAPIEndPoint("CANCEL_ORDER") + params))
            .setHeader("API-Key", api_key)
            .setHeader("API-Sign", signature)
            .build
        //send request and get response
        val response = httpClient.send(request, HttpResponse.BodyHandlers.ofString)
        // print status code
        println(response.statusCode)
        //print response message
        val status = response.statusCode
        if (status == 200) println("OK")
        // print response body
        println(response.body)
    }

    @throws[IOException]
    @throws[InterruptedException]
    @throws[NoSuchAlgorithmException]
    @throws[UnsupportedEncodingException]
    @throws[InvalidKeyException]
    def cancelling_open_order_per_instrument(instrument: String): Unit = {
        val payload = "\"\\\"\\\"\""
        val priv = new PrivateAPI(secret_key, api_key)
        val nonce = priv.getNonce
        val checksum = priv.getChecksum(payload)
        val nonce_checksum = priv.getNonceChecksum(nonce, checksum)
        val signature = priv.getSignature(config.baseURL.getPrivateAPIEndPoint("CANCEL_ORDER") + "/" + "instrument" + "/" + instrument, nonce_checksum)
        //construct query parameters
        val params = new StringBuilder()
            .append("?nonce=")
            .append(nonce.toLong)
            .append("&checksum=")
            .append(checksum)
            .append("&payload=")
            .append("")
            .toString
        //construct request body
        val request = HttpRequest.newBuilder
            .DELETE
            .uri(URI.create(config.baseURL.URL_API_BITWYRE + config.baseURL.getPrivateAPIEndPoint("CANCEL_ORDER") + "/" + "instrument" + "/" + instrument + params))
            .setHeader("API-Key", api_key)
            .setHeader("API-Sign", signature)
            .build
        //send request and get response
        val response = httpClient.send(request, HttpResponse.BodyHandlers.ofString)
        // print status code
        println(response.statusCode)
        //print response message
        val status = response.statusCode
        if (status == 200) println("OK")
        // print response body
        println(response.body)
    }
}
