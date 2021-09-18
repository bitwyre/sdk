package com.bitwyre.sdk;

import java.io.IOException;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.time.Duration;

public class PublicAPI {
    private static final HttpClient httpClient = HttpClient.newBuilder()
            .version(HttpClient.Version.HTTP_1_1)
            .connectTimeout(Duration.ofSeconds(5))
            .build();
    public static void get_server_time() throws IOException, InterruptedException {
        //using the new HTTP Client library starting from Java 11
        HttpRequest request = HttpRequest.newBuilder()
                .GET()
                .uri(URI.create(config.URL_API_BITWYRE + config.getPublicAPIEndPoint("SERVERTIME")))
                .setHeader("User-Agent", "Java SDK") // add request header
                .build();

        HttpResponse<String> response = httpClient.send(request, HttpResponse.BodyHandlers.ofString());

        // print status code
        System.out.println(response.statusCode());

        //print response message
        int status = response.statusCode();
        if (status == 200) {
            System.out.println("OK");;
        }

        // print response body
        System.out.println(response.body());
    } 
    public static void get_asset_pairs(String market, String product, String country) throws IOException, InterruptedException {
        String params = new StringBuilder()
            .append("market=")
            .append(market)
            .append("&product=")
            .append(product)
            .append("&country=")
            .append(country)
            .toString();
        //using the new HTTP Client library starting from Java 11
        HttpRequest request = HttpRequest.newBuilder()
                .GET()
                .uri(URI.create(config.URL_API_BITWYRE + config.getPublicAPIEndPoint("INSTRUMENT")+"?"+params))
                .setHeader("User-Agent", "Java SDK") // add request header
                .build();

        HttpResponse<String> response = httpClient.send(request, HttpResponse.BodyHandlers.ofString());

        // print status code
        System.out.println(response.statusCode());

        //print response message
        int status = response.statusCode();
        if (status == 200) {
            System.out.println("OK");;
        }

        // print response body
        System.out.println(response.body());
    } 
    public static void get_ticker(String instrument) throws IOException, InterruptedException {
        String params = new StringBuilder()
            .append("instrument=")
            .append(instrument)
            .toString();
        //using the new HTTP Client library starting from Java 11
        HttpRequest request = HttpRequest.newBuilder()
                .GET()
                .uri(URI.create(config.URL_API_BITWYRE + config.getPublicAPIEndPoint("TICKER")+"?"+params))
                .setHeader("User-Agent", "Java SDK") // add request header
                .build();

        HttpResponse<String> response = httpClient.send(request, HttpResponse.BodyHandlers.ofString());

        // print status code
        System.out.println(response.statusCode());

        //print response message
        int status = response.statusCode();
        if (status == 200) {
            System.out.println("OK");;
        }

        // print response body
        System.out.println(response.body());
    } 
    public static void get_trades(int trade_num, String instrument) throws IOException, InterruptedException {
        String params = new StringBuilder()
            .append("trade_num=")
            .append(trade_num)
            .append("&instrument=")
            .append(instrument)
            .toString();
        //using the new HTTP Client library starting from Java 11
        HttpRequest request = HttpRequest.newBuilder()
                .GET()
                .uri(URI.create(config.URL_API_BITWYRE + config.getPublicAPIEndPoint("TRADES")+"?"+params))
                .setHeader("User-Agent", "Java SDK") // add request header
                .build();

        HttpResponse<String> response = httpClient.send(request, HttpResponse.BodyHandlers.ofString());

        // print status code
        System.out.println(response.statusCode());

        //print response message
        int status = response.statusCode();
        if (status == 200) {
            System.out.println("OK");;
        }

        // print response body
        System.out.println(response.body());
    } 
    public static void get_depth(String instrument, int depth_num) throws IOException, InterruptedException {
        String params = new StringBuilder()
            .append("instrument=")
            .append(instrument)
            .append("&depth_num=")
            .append(depth_num)
            .toString();
        //using the new HTTP Client library starting from Java 11
        HttpRequest request = HttpRequest.newBuilder()
                .GET()
                .uri(URI.create(config.URL_API_BITWYRE + config.getPublicAPIEndPoint("DEPTH")+"?"+params))
                .setHeader("User-Agent", "Java SDK") // add request header
                .build();

        HttpResponse<String> response = httpClient.send(request, HttpResponse.BodyHandlers.ofString());

        // print status code
        System.out.println(response.statusCode());

        //print response message
        int status = response.statusCode();
        if (status == 200) {
            System.out.println("OK");;
        }

        // print response body
        System.out.println(response.body());
    } 
    public static void get_assets() throws IOException, InterruptedException {
        //using the new HTTP Client library starting from Java 11
        HttpRequest request = HttpRequest.newBuilder()
                .GET()
                .uri(URI.create(config.URL_API_BITWYRE + config.getPublicAPIEndPoint("ASSETS")))
                .setHeader("User-Agent", "Java SDK") // add request header
                .build();

        HttpResponse<String> response = httpClient.send(request, HttpResponse.BodyHandlers.ofString());

        // print status code
        System.out.println(response.statusCode());

        //print response message
        int status = response.statusCode();
        if (status == 200) {
            System.out.println("OK");;
        }

        // print response body
        System.out.println(response.body());
    } 
    public static void get_markets() throws IOException, InterruptedException {
        //using the new HTTP Client library starting from Java 11
        HttpRequest request = HttpRequest.newBuilder()
                .GET()
                .uri(URI.create(config.URL_API_BITWYRE + config.getPublicAPIEndPoint("MARKETS")))
                .setHeader("User-Agent", "Java SDK") // add request header
                .build();

        HttpResponse<String> response = httpClient.send(request, HttpResponse.BodyHandlers.ofString());

        // print status code
        System.out.println(response.statusCode());

        //print response message
        int status = response.statusCode();
        if (status == 200) {
            System.out.println("OK");;
        }

        // print response body
        System.out.println(response.body());
    } 
    public static void get_products() throws IOException, InterruptedException {
        //using the new HTTP Client library starting from Java 11
        HttpRequest request = HttpRequest.newBuilder()
                .GET()
                .uri(URI.create(config.URL_API_BITWYRE + config.getPublicAPIEndPoint("PRODUCTS")))
                .setHeader("User-Agent", "Java SDK") // add request header
                .build();

        HttpResponse<String> response = httpClient.send(request, HttpResponse.BodyHandlers.ofString());

        // print status code
        System.out.println(response.statusCode());

        //print response message
        int status = response.statusCode();
        if (status == 200) {
            System.out.println("OK");;
        }

        // print response body
        System.out.println(response.body());
    }
    public static void get_announcements() throws IOException, InterruptedException {
        //using the new HTTP Client library starting from Java 11
        HttpRequest request = HttpRequest.newBuilder()
                .GET()
                .uri(URI.create(config.URL_API_BITWYRE + config.getPublicAPIEndPoint("ANNOUNCEMENTS")))
                .setHeader("User-Agent", "Java SDK") // add request header
                .build();

        HttpResponse<String> response = httpClient.send(request, HttpResponse.BodyHandlers.ofString());

        // print status code
        System.out.println(response.statusCode());

        //print response message
        int status = response.statusCode();
        if (status == 200) {
            System.out.println("OK");;
        }

        // print response body
        System.out.println(response.body());
    }  
}
