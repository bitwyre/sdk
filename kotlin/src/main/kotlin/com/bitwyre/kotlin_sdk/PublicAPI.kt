package com.bitwyre.kotlin_sdk

import java.net.URI
import java.net.http.HttpClient
import java.net.http.HttpRequest
import java.net.http.HttpResponse

class PublicAPI {
    val client = HttpClient.newBuilder().build()
    fun getServerTime() {
        val request = HttpRequest.newBuilder()
            .GET()
            .uri(URI.create(Config.baseURL.URL_API_BITWYRE + Config.baseURL.getPublicAPIEndpoint("SERVERTIME")))
            .setHeader("User-Agent", "Kotlin SDK")
            .build()
        val response = client.send(request, HttpResponse.BodyHandlers.ofString())
        println(response.statusCode())
        val status = response.statusCode()
        if (status == 200) {
            println("OK")
        }
        println(response.body())
    }
    fun getAssetPairs(market: String, product: String, country: String) {
        val params = StringBuilder()
            .append("market=")
            .append(market)
            .append("&product=")
            .append(product)
            .append("&country=")
            .append(country)
            .toString()
        val request = HttpRequest.newBuilder()
            .GET()
            .uri(URI.create(Config.baseURL.URL_API_BITWYRE + Config.baseURL.getPublicAPIEndpoint("INSTRUMENT") + "?" + params))
            .setHeader("User-Agent", "Kotlin SDK")
            .build()
        val response = client.send(request, HttpResponse.BodyHandlers.ofString())
        println(response.statusCode())
        val status = response.statusCode()
        if (status == 200) {
            println("OK")
        }
        println(response.body())
    }
    fun getTicker(instrument: String) {
        val params = StringBuilder()
            .append("instrument=")
            .append(instrument)
            .toString()
        val request = HttpRequest.newBuilder()
            .GET()
            .uri(URI.create(Config.baseURL.URL_API_BITWYRE + Config.baseURL.getPublicAPIEndpoint("TICKER") + "?" + params))
            .setHeader("User-Agent", "Kotlin SDK")
            .build()
        val response = client.send(request, HttpResponse.BodyHandlers.ofString())
        println(response.statusCode())
        val status = response.statusCode()
        if (status == 200) {
            println("OK")
        }
        println(response.body())
    }
    fun getTrades(trade_num: Int, instrument: String) {
        val params = StringBuilder()
            .append("trade_num=")
            .append(trade_num)
            .append("&instrument=")
            .append(instrument)
            .toString()
        val request = HttpRequest.newBuilder()
            .GET()
            .uri(URI.create(Config.baseURL.URL_API_BITWYRE + Config.baseURL.getPublicAPIEndpoint("TRADES") + "?" + params))
            .setHeader("User-Agent", "Kotlin SDK")
            .build()
        val response = client.send(request, HttpResponse.BodyHandlers.ofString())
        println(response.statusCode())
        val status = response.statusCode()
        if (status == 200) {
            println("OK")
        }
        println(response.body())
    }
    fun getDepth(instrument: String, depth_num: Int) {
        val params = StringBuilder()
            .append("instrument=")
            .append(instrument)
            .append("&depth_num=")
            .append(depth_num)
            .toString()
        val request = HttpRequest.newBuilder()
            .GET()
            .uri(URI.create(Config.baseURL.URL_API_BITWYRE + Config.baseURL.getPublicAPIEndpoint("DEPTH") + "?" + params))
            .setHeader("User-Agent", "Kotlin SDK")
            .build()
        val response = client.send(request, HttpResponse.BodyHandlers.ofString())
        println(response.statusCode())
        val status = response.statusCode()
        if (status == 200) {
            println("OK")
        }
        println(response.body())
    }
    fun getAssets() {
        val request = HttpRequest.newBuilder()
            .GET()
            .uri(URI.create(Config.baseURL.URL_API_BITWYRE + Config.baseURL.getPublicAPIEndpoint("ASSETS")))
            .setHeader("User-Agent", "Kotlin SDK")
            .build()
        val response = client.send(request, HttpResponse.BodyHandlers.ofString())
        println(response.statusCode())
        val status = response.statusCode()
        if (status == 200) {
            println("OK")
        }
        println(response.body())
    }
    fun getMarkets() {
        val request = HttpRequest.newBuilder()
            .GET()
            .uri(URI.create(Config.baseURL.URL_API_BITWYRE + Config.baseURL.getPublicAPIEndpoint("MARKETS")))
            .setHeader("User-Agent", "Kotlin SDK")
            .build()
        val response = client.send(request, HttpResponse.BodyHandlers.ofString())
        println(response.statusCode())
        val status = response.statusCode()
        if (status == 200) {
            println("OK")
        }
        println(response.body())
    }
    fun getProducts() {
        val request = HttpRequest.newBuilder()
            .GET()
            .uri(URI.create(Config.baseURL.URL_API_BITWYRE + Config.baseURL.getPublicAPIEndpoint("PRODUCTS")))
            .setHeader("User-Agent", "Kotlin SDK")
            .build()
        val response = client.send(request, HttpResponse.BodyHandlers.ofString())
        println(response.statusCode())
        val status = response.statusCode()
        if (status == 200) {
            println("OK")
        }
        println(response.body())
    }
    fun getAnnouncements() {
        val request = HttpRequest.newBuilder()
            .GET()
            .uri(URI.create(Config.baseURL.URL_API_BITWYRE + Config.baseURL.getPublicAPIEndpoint("ANNOUNCEMENTS")))
            .setHeader("User-Agent", "Kotlin SDK")
            .build()
        val response = client.send(request, HttpResponse.BodyHandlers.ofString())
        println(response.statusCode())
        val status = response.statusCode()
        if (status == 200) {
            println("OK")
        }
        println(response.body())
    }
}