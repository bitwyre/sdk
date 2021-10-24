package com.bitwyre.scala_sdk

import java.io.IOException
import java.net.URI
import java.net.http.HttpRequest
import java.net.http.HttpResponse
import java.net.http.HttpClient
import java.time.Duration
import com.bitwyre.scala_sdk.Config

class PublicAPI {
    val httpClient = HttpClient.newBuilder
        .version(HttpClient.Version.HTTP_1_1)
        .connectTimeout(Duration.ofSeconds(5))
        .build

    @throws[IOException]
    @throws[InterruptedException]
    def get_server_time(): Unit = {
        //using the new HTTP Client library starting from Java 11
        val config = new Config()
        val request = HttpRequest.newBuilder
            .GET
            .uri(URI.create(config.baseURL.URL_API_BITWYRE + config.baseURL.getPublicAPIEndpoint("SERVERTIME")))
            .setHeader("User-Agent", "Scala SDK") // add request header
            .build

        val response = httpClient.send(request, HttpResponse.BodyHandlers.ofString)

        // print status code
        println(response.statusCode)

        //print response message
        val status = response.statusCode
        if (status == 200) then
            println("OK")

        // print response body
        println(response.body)
    }

    @throws[IOException]
    @throws[InterruptedException]
    def get_asset_pairs(market: String, product: String, country: String): Unit = {
        val params = new StringBuilder()
            .append("market=")
            .append(market)
            .append("&product=")
            .append(product)
            .append("&country=")
            .append(country)
            .toString

        //using the new HTTP Client library starting from Java 11
        val config = new Config()
        val request = HttpRequest.newBuilder
            .GET
            .uri(URI.create(config.baseURL.URL_API_BITWYRE + config.baseURL.getPublicAPIEndpoint("INSTRUMENT") + "?" + params))
            .setHeader("User-Agent", "Scala SDK") // add request header
            .build

        val response = httpClient.send(request, HttpResponse.BodyHandlers.ofString)

        // print status code
        println(response.statusCode)

        //print response message
        val status = response.statusCode
        if (status == 200) then
            println("OK")

        // print response body
        println(response.body)
    }

    @throws[IOException]
    @throws[InterruptedException]
    def get_ticker(instrument: String): Unit = {
        val params = new StringBuilder()
            .append("instrument=")
            .append(instrument)
            .toString

        //using the new HTTP Client library starting from Java 11
        val config = new Config()
        val request = HttpRequest.newBuilder
            .GET
            .uri(URI.create(config.baseURL.URL_API_BITWYRE + config.baseURL.getPublicAPIEndpoint("TICKER") + "?" + params))
            .setHeader("User-Agent", "Scala SDK") // add request header
            .build

        val response = httpClient.send(request, HttpResponse.BodyHandlers.ofString)

        // print status code
        println(response.statusCode)

        //print response message
        val status = response.statusCode
        if (status == 200) then
            println("OK")

        // print response body
        println(response.body)
    }

    @throws[IOException]
    @throws[InterruptedException]
    def get_trades(trade_num: Int, instrument: String): Unit = {
        val params = new StringBuilder()
            .append("trade_num=")
            .append(trade_num)
            .append("&instrument=")
            .append(instrument)
            .toString

        //using the new HTTP Client library starting from Java 11
        val config = new Config()
        val request = HttpRequest.newBuilder
            .GET
            .uri(URI.create(config.baseURL.URL_API_BITWYRE + config.baseURL.getPublicAPIEndpoint("TRADES") + "?" + params))
            .setHeader("User-Agent", "Scala SDK") // add request header
            .build

        val response = httpClient.send(request, HttpResponse.BodyHandlers.ofString)

        // print status code
        println(response.statusCode)

        //print response message
        val status = response.statusCode
        if (status == 200) then
            println("OK")

        // print response body
        println(response.body)
    }

    @throws[IOException]
    @throws[InterruptedException]
    def get_depth(instrument: String, depth_num: Int): Unit = {
        val params = new StringBuilder()
            .append("instrument=")
            .append(instrument)
            .append("&depth_num=")
            .append(depth_num)
            .toString

        //using the new HTTP Client library starting from Java 11
        val config = new Config()
        val request = HttpRequest.newBuilder
            .GET
            .uri(URI.create(config.baseURL.URL_API_BITWYRE + config.baseURL.getPublicAPIEndpoint("DEPTH") + "?" + params))
            .setHeader("User-Agent", "Scala SDK") // add request header
            .build

        val response = httpClient.send(request, HttpResponse.BodyHandlers.ofString)

        // print status code
        println(response.statusCode)

        //print response message
        val status = response.statusCode
        if (status == 200) then
            println("OK")

        // print response body
        println(response.body)
    }

    @throws[IOException]
    @throws[InterruptedException]
    def get_assets(): Unit = {
        //using the new HTTP Client library starting from Java 11
        val config = new Config()
        val request = HttpRequest.newBuilder
            .GET
            .uri(URI.create(config.baseURL.URL_API_BITWYRE + config.baseURL.getPublicAPIEndpoint("ASSETS")))
            .setHeader("User-Agent", "Scala SDK") // add request header
            .build

        val response = httpClient.send(request, HttpResponse.BodyHandlers.ofString)

        // print status code
        println(response.statusCode)

        //print response message
        val status = response.statusCode
        if (status == 200) then
            println("OK")

        // print response body
        println(response.body)
    }

    @throws[IOException]
    @throws[InterruptedException]
    def get_markets(): Unit = {
        //using the new HTTP Client library starting from Java 11
        val config = new Config()
        val request = HttpRequest.newBuilder
            .GET
            .uri(URI.create(config.baseURL.URL_API_BITWYRE + config.baseURL.getPublicAPIEndpoint("MARKETS")))
            .setHeader("User-Agent", "Scala SDK") // add request header
            .build

        val response = httpClient.send(request, HttpResponse.BodyHandlers.ofString)

        // print status code
        println(response.statusCode)

        //print response message
        val status = response.statusCode
        if (status == 200) then
            println("OK")

        // print response body
        println(response.body)
    }

    @throws[IOException]
    @throws[InterruptedException]
    def get_products(): Unit = {
        //using the new HTTP Client library starting from Java 11
        val config = new Config()
        val request = HttpRequest.newBuilder
            .GET
            .uri(URI.create(config.baseURL.URL_API_BITWYRE + config.baseURL.getPublicAPIEndpoint("PRODUCTS")))
            .setHeader("User-Agent", "Scala SDK") // add request header
            .build

        val response = httpClient.send(request, HttpResponse.BodyHandlers.ofString)

        // print status code
        println(response.statusCode)

        //print response message
        val status = response.statusCode
        if (status == 200) then
            println("OK")

        // print response body
        println(response.body)
    }

    @throws[IOException]
    @throws[InterruptedException]
    def get_announcements(): Unit = {
        //using the new HTTP Client library starting from Java 11
        val config = new Config()
        val request = HttpRequest.newBuilder
            .GET
            .uri(URI.create(config.baseURL.URL_API_BITWYRE + config.baseURL.getPublicAPIEndpoint("ANNOUNCEMENTS")))
            .setHeader("User-Agent", "Scala SDK") // add request header
            .build

        val response = httpClient.send(request, HttpResponse.BodyHandlers.ofString)

        // print status code
        println(response.statusCode)

        //print response message
        val status = response.statusCode
        if (status == 200) then
            println("OK")

        // print response body
        println(response.body)
    }
}
