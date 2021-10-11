package com.bitwyre.kotlin_sdk

import java.io.IOException
import java.io.UnsupportedEncodingException
import java.net.URI
import java.net.URLEncoder
import java.net.http.HttpClient
import java.net.http.HttpRequest
import java.net.http.HttpResponse
import java.security.InvalidKeyException
import java.security.MessageDigest
import java.security.NoSuchAlgorithmException
import java.time.Duration
import java.time.Instant
import javax.crypto.Mac
import javax.crypto.spec.SecretKeySpec


class PrivateAPI constructor(secretkey: String, apikey: String) {
    val secretkey: String
    val apikey: String
    init {
        this.secretkey = secretkey
        this.apikey = apikey
    }
    val client = HttpClient.newBuilder()
        .version(HttpClient.Version.HTTP_1_1)
        .connectTimeout(Duration.ofSeconds(Config.baseURL.TIMEOUT.toLong()))
        .build()
    fun getNonce(): String {
        val instant = Instant.now()
        val secondsSinceEpoch = instant.epochSecond
        val nanoSeconds = instant.nano.toLong()
        return StringBuilder().append(secondsSinceEpoch).append(nanoSeconds).toString()
    }

    @Throws(NoSuchAlgorithmException::class, UnsupportedEncodingException::class)
    fun getChecksum(payload: String): String? {
        val md = MessageDigest.getInstance("SHA-256")
        md.update(payload.toByteArray(charset("UTF-8")))
        val checksum = md.digest()
        val hexString = StringBuffer()
        for (i in checksum.indices) {
            val hex = Integer.toHexString(0xFF and checksum[i].toInt())
            if (hex.length == 1) {
                hexString.append("0")
            }
            hexString.append(hex)
        }
        return hexString.toString()
    }

    @Throws(NoSuchAlgorithmException::class, UnsupportedEncodingException::class)
    fun getNonceChecksum(nonce: String?, checksum: String?): String? {
        val temp = StringBuilder().append(nonce).append(checksum).toString()
        val mdgDigest = MessageDigest.getInstance("SHA-256")
        mdgDigest.update(temp.toByteArray(charset("UTF-8")))
        val nonce_checksum = mdgDigest.digest()
        val hexStr = StringBuffer()
        for (i in nonce_checksum.indices) {
            val hxa = Integer.toHexString(0xFF and nonce_checksum[i].toInt())
            if (hxa.length == 1) {
                hexStr.append("0")
            }
            hexStr.append(hxa)
        }
        return hexStr.toString()
    }

    @Throws(NoSuchAlgorithmException::class, UnsupportedEncodingException::class, InvalidKeyException::class)
    fun getSignature(uri_path: String?, nonce_checksum: String?): String? {
        val data = StringBuilder().append(uri_path).append(nonce_checksum).toString()
        val sha512_HMAC = Mac.getInstance("HmacSHA512")
        val key = SecretKeySpec(secretkey.toByteArray(charset("UTF-8")),"HmacSHA512")
        sha512_HMAC.init(key)
        val hash = sha512_HMAC.doFinal(data.toByteArray(charset("UTF-8")))
        val hexSign = StringBuffer()
        for (i in hash.indices) {
            val hexa = Integer.toHexString(0xFF and hash[i].toInt())
            if (hexa.length == 1) {
                hexSign.append("0")
            }
            hexSign.append(hexa)
        }
        return hexSign.toString()
    }

    @Throws(
        IOException::class,
        InterruptedException::class,
        NoSuchAlgorithmException::class,
        UnsupportedEncodingException::class,
        InvalidKeyException::class
    )
    fun get_account_balance() {
        val payload = "\"\\\"\\\"\""
        val priv = PrivateAPI(secretkey, apikey)
        val nonce: String = priv.getNonce()
        val checksum = priv.getChecksum(payload)
        val nonce_checksum = priv.getNonceChecksum(nonce, checksum)
        val signature = priv.getSignature(Config.baseURL.getPrivateAPIEndPoint("ACCOUNT_BALANCE"), nonce_checksum)

        //construct query parameters
        val params = StringBuilder()
            .append("?nonce=")
            .append(java.lang.Long.valueOf(nonce))
            .append("&checksum=")
            .append(checksum)
            .append("&payload=")
            .append("")
            .toString()

        //construct request body
        val request = HttpRequest.newBuilder()
            .GET()
            .uri(
                URI.create(
                    Config.baseURL.URL_API_BITWYRE + Config.baseURL.getPrivateAPIEndPoint("ACCOUNT_BALANCE") + params
                )
            )
            .setHeader("API-Key", apikey)
            .setHeader("API-Sign", signature)
            .build()

        //send request and get response
        val response: HttpResponse<String> = client.send(request, HttpResponse.BodyHandlers.ofString())

        // print status code
        println(response.statusCode())

        //print response message
        val status = response.statusCode()
        if (status == 200) {
            println("OK")
        }

        // print response body
        println(response.body())
    }

    @Throws(
        IOException::class,
        InterruptedException::class,
        NoSuchAlgorithmException::class,
        UnsupportedEncodingException::class,
        InvalidKeyException::class
    )
    fun get_account_statement() {
        val payload = "\"\\\"\\\"\""
        val priv = PrivateAPI(secretkey, apikey)
        val nonce = priv.getNonce()
        val checksum = priv.getChecksum(payload)
        val nonce_checksum = priv.getNonceChecksum(nonce, checksum)
        val signature = priv.getSignature(Config.baseURL.getPrivateAPIEndPoint("ACCOUNT_STATEMENT"), nonce_checksum)

        //construct query parameters
        val params = StringBuilder()
            .append("?nonce=")
            .append(java.lang.Long.valueOf(nonce))
            .append("&checksum=")
            .append(checksum)
            .append("&payload=")
            .append("")
            .toString()

        //construct request body
        val request = HttpRequest.newBuilder()
            .GET()
            .uri(
                URI.create(
                    Config.baseURL.URL_API_BITWYRE + Config.baseURL.getPrivateAPIEndPoint("ACCOUNT_STATEMENT") + params
                )
            )
            .setHeader("API-Key", apikey)
            .setHeader("API-Sign", signature)
            .build()

        //send request and get response
        val response: HttpResponse<String> = client.send(request, HttpResponse.BodyHandlers.ofString())

        // print status code
        println(response.statusCode())

        //print response message
        val status = response.statusCode()
        if (status == 200) {
            println("OK")
        }

        // print response body
        println(response.body())
    }

    @Throws(
        IOException::class,
        InterruptedException::class,
        NoSuchAlgorithmException::class,
        UnsupportedEncodingException::class,
        InvalidKeyException::class
    )
    fun get_transaction_histories() {
        val payload = "\"\\\"\\\"\""
        val priv = PrivateAPI(secretkey, apikey)
        val nonce = priv.getNonce()
        val checksum = priv.getChecksum(payload)
        val nonce_checksum = priv.getNonceChecksum(nonce, checksum)
        val signature = priv.getSignature(Config.baseURL.getPrivateAPIEndPoint("TRANSACTION_HISTORIES"), nonce_checksum)

        //construct query parameters
        val params = StringBuilder()
            .append("?nonce=")
            .append(java.lang.Long.valueOf(nonce))
            .append("&checksum=")
            .append(checksum)
            .append("&payload=")
            .append("")
            .toString()

        //construct request body
        val request = HttpRequest.newBuilder()
            .GET()
            .uri(
                URI.create(
                    Config.baseURL.URL_API_BITWYRE + Config.baseURL.getPrivateAPIEndPoint("TRANSACTION_HISTORIES") + params
                )
            )
            .setHeader("API-Key", apikey)
            .setHeader("API-Sign", signature)
            .build()

        //send request and get response
        val response: HttpResponse<String> = client.send(request, HttpResponse.BodyHandlers.ofString())

        // print status code
        println(response.statusCode())

        //print response message
        val status = response.statusCode()
        if (status == 200) {
            println("OK")
        }

        // print response body
        println(response.body())
    }

    @Throws(
        IOException::class,
        InterruptedException::class,
        NoSuchAlgorithmException::class,
        UnsupportedEncodingException::class,
        InvalidKeyException::class
    )
    fun get_open_orders(instrument: String, from_time: Int, to_time: Int) {
        val payload = "\"\\\"{\\\\\\\"instrument\\\\\\\":\\\\\\\"$instrument\\\\\\\",\\\\\\\"from_time\\\\\\\":$from_time,\\\\\\\"to_time\\\\\\\":$to_time}\\\"\""
        val priv = PrivateAPI(secretkey, apikey)
        val nonce = priv.getNonce()
        val checksum = priv.getChecksum(payload)
        val nonce_checksum = priv.getNonceChecksum(nonce, checksum)
        val signature = priv.getSignature(Config.baseURL.getPrivateAPIEndPoint("OPEN_ORDERS"), nonce_checksum)
        val payload2 = "{\"instrument\":\"$instrument\",\"from_time\":$from_time,\"to_time\":$to_time}"
        val encodedPayload = URLEncoder.encode(payload2, "UTF-8")

        //construct query parameters
        val params = StringBuilder()
            .append("?nonce=")
            .append(java.lang.Long.valueOf(nonce))
            .append("&checksum=")
            .append(checksum)
            .append("&payload=")
            .append(encodedPayload)
            .toString()

        //construct request body
        val request = HttpRequest.newBuilder()
            .GET()
            .uri(
                URI.create(
                    Config.baseURL.URL_API_BITWYRE + Config.baseURL.getPrivateAPIEndPoint("OPEN_ORDERS") + params
                )
            )
            .setHeader("API-Key", apikey)
            .setHeader("API-Sign", signature)
            .build()

        //send request and get response
        val response: HttpResponse<String> = client.send(request, HttpResponse.BodyHandlers.ofString())

        // print status code
        println(response.statusCode())

        //print response message
        val status = response.statusCode()
        if (status == 200) {
            println("OK")
        }

        // print response body
        println(response.body())
    }

    @Throws(
        IOException::class,
        InterruptedException::class,
        NoSuchAlgorithmException::class,
        UnsupportedEncodingException::class,
        InvalidKeyException::class
    )
    fun get_closed_orders(instrument: String, from_time: Int, to_time: Int) {
        val payload = "\"\\\"{\\\\\\\"instrument\\\\\\\":\\\\\\\"$instrument\\\\\\\",\\\\\\\"from_time\\\\\\\":$from_time,\\\\\\\"to_time\\\\\\\":$to_time}\\\"\""
        val priv = PrivateAPI(secretkey, apikey)
        val nonce = priv.getNonce()
        val checksum = priv.getChecksum(payload)
        val nonce_checksum = priv.getNonceChecksum(nonce, checksum)
        val signature = priv.getSignature(Config.baseURL.getPrivateAPIEndPoint("CLOSED_ORDERS"), nonce_checksum)
        val payload2 = "{\"instrument\":\"$instrument\",\"from_time\":$from_time,\"to_time\":$to_time}"
        val encodedPayload = URLEncoder.encode(payload2, "UTF-8")

        //construct query parameters
        val params = StringBuilder()
            .append("?nonce=")
            .append(java.lang.Long.valueOf(nonce))
            .append("&checksum=")
            .append(checksum)
            .append("&payload=")
            .append(encodedPayload)
            .toString()

        //construct request body
        val request = HttpRequest.newBuilder()
            .GET()
            .uri(
                URI.create(
                    Config.baseURL.URL_API_BITWYRE + Config.baseURL.getPrivateAPIEndPoint("CLOSED_ORDERS") + params
                )
            )
            .setHeader("API-Key", apikey)
            .setHeader("API-Sign", signature)
            .build()

        //send request and get response
        val response: HttpResponse<String> = client.send(request, HttpResponse.BodyHandlers.ofString())

        // print status code
        println(response.statusCode())

        //print response message
        val status = response.statusCode()
        if (status == 200) {
            println("OK")
        }

        // print response body
        println(response.body())
    }

    @Throws(
        IOException::class,
        InterruptedException::class,
        NoSuchAlgorithmException::class,
        UnsupportedEncodingException::class,
        InvalidKeyException::class
    )
    fun get_order_info(order_id: String) {
        val payload = "\"\\\"\\\"\""
        val priv = PrivateAPI(secretkey, apikey)
        val nonce = priv.getNonce()
        val checksum = priv.getChecksum(payload)
        val nonce_checksum = priv.getNonceChecksum(nonce, checksum)
        val signature = priv.getSignature(Config.baseURL.getPrivateAPIEndPoint("ORDER_INFO") + "/" + order_id, nonce_checksum)

        //construct query parameters
        val params = StringBuilder()
            .append("?nonce=")
            .append(java.lang.Long.valueOf(nonce))
            .append("&checksum=")
            .append(checksum)
            .append("&payload=")
            .append("")
            .toString()

        //construct request body
        val request = HttpRequest.newBuilder()
            .GET()
            .uri(
                URI.create(
                    Config.baseURL.URL_API_BITWYRE + Config.baseURL.getPrivateAPIEndPoint("ORDER_INFO") + "/" + order_id + params
                )
            )
            .setHeader("API-Key", apikey)
            .setHeader("API-Sign", signature)
            .build()

        //send request and get response
        val response: HttpResponse<String> = client.send(request, HttpResponse.BodyHandlers.ofString())

        // print status code
        println(response.statusCode())

        //print response message
        val status = response.statusCode()
        if (status == 200) {
            println("OK")
        }

        // print response body
        println(response.body())
    }

    @Throws(
        IOException::class,
        InterruptedException::class,
        NoSuchAlgorithmException::class,
        UnsupportedEncodingException::class,
        InvalidKeyException::class
    )
    fun get_trade_history(instrument: String, count: Int, from_time: Int, to_time: Int) {
        val payload = "\"\\\"{\\\\\\\"instrument\\\\\\\":\\\\\\\"$instrument\\\\\\\",\\\\\\\"count\\\\\\\":$count,\\\\\\\"from_time\\\\\\\":$from_time,\\\\\\\"to_time\\\\\\\":$to_time}\\\"\""
        val priv = PrivateAPI(secretkey, apikey)
        val nonce = priv.getNonce()
        val checksum = priv.getChecksum(payload)
        val nonce_checksum = priv.getNonceChecksum(nonce, checksum)
        val signature = priv.getSignature(Config.baseURL.getPrivateAPIEndPoint("TRADE_HISTORY"), nonce_checksum)
        val payload2 = "{\"instrument\":\"$instrument\",\"count\":$count,\"from_time\":$from_time,\"to_time\":$to_time}"
        val encodedPayload = URLEncoder.encode(payload2, "UTF-8")

        //construct query parameters
        val params = StringBuilder()
            .append("?nonce=")
            .append(java.lang.Long.valueOf(nonce))
            .append("&checksum=")
            .append(checksum)
            .append("&payload=")
            .append(encodedPayload)
            .toString()

        //construct request body
        val request = HttpRequest.newBuilder()
            .GET()
            .uri(
                URI.create(
                    Config.baseURL.URL_API_BITWYRE + Config.baseURL.getPrivateAPIEndPoint("TRADE_HISTORY") + params
                )
            )
            .setHeader("API-Key", apikey)
            .setHeader("API-Sign", signature)
            .build()

        //send request and get response
        val response: HttpResponse<String> = client.send(request, HttpResponse.BodyHandlers.ofString())

        // print status code
        println(response.statusCode())

        //print response message
        val status = response.statusCode()
        if (status == 200) {
            println("OK")
        }

        // print response body
        println(response.body())
    }

    @Throws(
        IOException::class,
        InterruptedException::class,
        NoSuchAlgorithmException::class,
        UnsupportedEncodingException::class,
        InvalidKeyException::class
    )
    fun opening_new_order(
        instrument: String,
        side: Int,
        price: String,
        ordtype: Int,
        orderqty: String
    ) {
        val payload = "\"\\\"{\\\\\\\"instrument\\\\\\\":\\\\\\\"" + instrument + "\\\\\\\",\\\\\\\"side\\\\\\\":" + side + ",\\\\\\\"price\\\\\\\":\\\\\\\"" + price +
                    "\\\\\\\",\\\\\\\"ordtype\\\\\\\":" + ordtype + ",\\\\\\\"orderqty\\\\\\\":\\\\\\\"" + orderqty + "\\\\\\\"}\\\"\""
        val priv = PrivateAPI(secretkey, apikey)
        val nonce = priv.getNonce()
        val checksum = priv.getChecksum(payload)
        val nonce_checksum = priv.getNonceChecksum(nonce, checksum)
        val signature = priv.getSignature(Config.baseURL.getPrivateAPIEndPoint("ORDER"), nonce_checksum)
        val payload2 = "{\\\"instrument\\\":" + "\\\"" + instrument + "\\\"" + ",\\\"side\\\":" + side + ",\\\"price\\\":" + "\\\"" + price + "\\\"" + ",\\\"ordtype\\\":" + ordtype +
                    ",\\\"orderqty\\\":" + "\\\"" + orderqty + "\\\"" + "}"

        //construct query parameters
        val data = StringBuilder()
            .append("{")
            .append("\"nonce\":")
            .append(java.lang.Long.valueOf(nonce))
            .append(",\"checksum\":")
            .append("\"")
            .append(checksum)
            .append("\"")
            .append(",\"payload\":")
            .append("\"")
            .append(payload2)
            .append("\"")
            .append("}")
            .toString()

        //construct request body
        val request = HttpRequest.newBuilder()
            .POST(HttpRequest.BodyPublishers.ofString(data))
            .uri(URI.create(Config.baseURL.URL_API_BITWYRE + Config.baseURL.getPrivateAPIEndPoint("ORDER")))
            .setHeader("API-Key", apikey)
            .setHeader("API-Sign", signature)
            .setHeader("Content-Type", "application/json")
            .build()

        //send request and get response
        val response: HttpResponse<String> = client.send(request, HttpResponse.BodyHandlers.ofString())

        // print status code
        println(response.statusCode())

        //print response message
        val status = response.statusCode()
        if (status == 200) {
            println("OK")
        }

        // print response body
        println(response.body())
    }

    @Throws(
        IOException::class,
        InterruptedException::class,
        NoSuchAlgorithmException::class,
        UnsupportedEncodingException::class,
        InvalidKeyException::class
    )
    fun cancelling_open_order(order_ids: Array<String>, qtys: Array<Int>) {
        //Converting Array to List
        val list: MutableList<String> = ArrayList()
        for (id in order_ids) {
            list.add(id)
        }
        val list2: MutableList<Int> = ArrayList()
        for (qty in qtys) {
            list2.add(qty)
        }
        var j: Int
        var orderids = ""
        for (i in order_ids.indices) {
            j = i + 1
            orderids = orderids + "\\\\\\\"" + order_ids[i] + "\\\\\\\""
            if (j != order_ids.size) {
                orderids = "$orderids,"
            }
        }
        var k: Int
        var temp = ""
        for (i in qtys.indices) {
            k = i + 1
            temp += qtys[i]
            if (k != qtys.size) {
                temp = "$temp,"
            }
        }
        val payload = "\"\\\"{\\\\\\\"order_ids\\\\\\\":[$orderids],\\\\\\\"qtys\\\\\\\":[$temp]}\\\"\""
        val priv = PrivateAPI(secretkey, apikey)
        val nonce = priv.getNonce()
        val checksum = priv.getChecksum(payload)
        val nonce_checksum = priv.getNonceChecksum(nonce, checksum)
        val signature = priv.getSignature(Config.baseURL.getPrivateAPIEndPoint("CANCEL_ORDER"), nonce_checksum)
        var l: Int
        var orderids2 = ""
        for (i in order_ids.indices) {
            l = i + 1
            orderids2 = orderids2 + "\"" + order_ids[i] + "\""
            if (l != order_ids.size) {
                orderids2 = "$orderids2,"
            }
        }
        var m: Int
        var temp2 = ""
        for (i in qtys.indices) {
            m = i + 1
            temp2 += qtys[i]
            if (m != qtys.size) {
                temp2 = "$temp2,"
            }
        }
        val payload2 = "{\"order_ids\":[$orderids2],\"qtys\":[$temp2]}"
        val encodedPayload = URLEncoder.encode(payload2, "UTF-8")

        //construct query parameters
        val params = StringBuilder()
            .append("?nonce=")
            .append(java.lang.Long.valueOf(nonce))
            .append("&checksum=")
            .append(checksum)
            .append("&payload=")
            .append(encodedPayload)
            .toString()

        //construct request body
        val request = HttpRequest.newBuilder()
            .DELETE()
            .uri(
                URI.create(
                    Config.baseURL.URL_API_BITWYRE + Config.baseURL.getPrivateAPIEndPoint("CANCEL_ORDER") + params
                )
            )
            .setHeader("API-Key", apikey)
            .setHeader("API-Sign", signature)
            .build()

        //send request and get response
        val response: HttpResponse<String> = client.send(request, HttpResponse.BodyHandlers.ofString())

        // print status code
        println(response.statusCode())

        //print response message
        val status = response.statusCode()
        if (status == 200) {
            println("OK")
        }

        // print response body
        println(response.body())
    }

    @Throws(
        IOException::class,
        InterruptedException::class,
        NoSuchAlgorithmException::class,
        UnsupportedEncodingException::class,
        InvalidKeyException::class
    )
    fun cancelling_open_order_per_instrument(instrument: String) {
        val payload = "\"\\\"\\\"\""
        val priv = PrivateAPI(secretkey, apikey)
        val nonce = priv.getNonce()
        val checksum = priv.getChecksum(payload)
        val nonce_checksum = priv.getNonceChecksum(nonce, checksum)
        val signature = priv.getSignature(
            Config.baseURL.getPrivateAPIEndPoint("CANCEL_ORDER") + "/" + "instrument" + "/" + instrument,
            nonce_checksum
        )

        //construct query parameters
        val params = StringBuilder()
            .append("?nonce=")
            .append(java.lang.Long.valueOf(nonce))
            .append("&checksum=")
            .append(checksum)
            .append("&payload=")
            .append("")
            .toString()

        //construct request body
        val request = HttpRequest.newBuilder()
            .DELETE()
            .uri(
                URI.create(
                    Config.baseURL.URL_API_BITWYRE + Config.baseURL.getPrivateAPIEndPoint("CANCEL_ORDER")
                            + "/" + "instrument" + "/" + instrument + params
                )
            )
            .setHeader("API-Key", apikey)
            .setHeader("API-Sign", signature)
            .build()

        //send request and get response
        val response: HttpResponse<String> = client.send(request, HttpResponse.BodyHandlers.ofString())

        // print status code
        println(response.statusCode())

        //print response message
        val status = response.statusCode()
        if (status == 200) {
            println("OK")
        }

        // print response body
        println(response.body())
    }
}


