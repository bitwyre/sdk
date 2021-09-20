package com.bitwyre.sdk;

import java.io.IOException;
import java.net.URI;
import java.net.URLEncoder;
import java.net.http.HttpClient;
import java.net.http.HttpHeaders;
import java.net.http.HttpRequest;
import java.net.http.HttpRequest.BodyPublishers;
import java.net.http.HttpResponse;
import java.time.*;
import java.security.InvalidKeyException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import javax.crypto.Mac;
import javax.crypto.spec.SecretKeySpec;
import java.io.*;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List; 

public class PrivateAPI {
    private String secret_key, api_key;
    public PrivateAPI(String secret_key, String api_key) {
        this.secret_key = secret_key;
        this.api_key = api_key;
    }
    private static final HttpClient httpClient = HttpClient.newBuilder()
        .version(HttpClient.Version.HTTP_1_1)
        .connectTimeout(Duration.ofSeconds(5))
        .build();
    public String getNonce() {
        Instant instant = Instant.now();
        long secondsSinceEpoch = instant.getEpochSecond();
        long nanoSeconds = instant.getNano();
        String nonce = new StringBuilder().append(secondsSinceEpoch).append(nanoSeconds).toString();
        return nonce;
    }
    public String getChecksum(String payload) throws NoSuchAlgorithmException, UnsupportedEncodingException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(payload.getBytes("UTF-8"));
        byte[] checksum = md.digest();
        StringBuffer hexString = new StringBuffer();
        for (int i = 0;i<checksum.length;i++) {
            String hex = Integer.toHexString(0xFF & checksum[i]);
            if (hex.length() == 1) {
                hexString.append("0");
            }
            hexString.append(hex);
        }
        return hexString.toString();
    }
    public String getNonceChecksum(String nonce, String checksum) throws NoSuchAlgorithmException, UnsupportedEncodingException {
        String temp = new StringBuilder().append(nonce).append(checksum).toString();
        MessageDigest mdgDigest = MessageDigest.getInstance("SHA-256");
        mdgDigest.update(temp.getBytes("UTF-8"));
        byte[] nonce_checksum = mdgDigest.digest();
        StringBuffer hexStr = new StringBuffer();
        for (int i = 0;i<nonce_checksum.length;i++) {
            String hxa = Integer.toHexString(0xFF & nonce_checksum[i]);
            if (hxa.length() == 1) {
                hexStr.append("0");
            }
            hexStr.append(hxa);
        }
        return hexStr.toString();
    }
    public String getSignature(String uri_path, String nonce_checksum) throws NoSuchAlgorithmException, UnsupportedEncodingException, InvalidKeyException {
        String data = new StringBuilder().append(uri_path).append(nonce_checksum).toString();
        Mac sha512_HMAC = Mac.getInstance("HmacSHA512");
        SecretKeySpec key = new SecretKeySpec(secret_key.getBytes("UTF-8"), "HmacSHA512");
        sha512_HMAC.init(key);
        byte[] hash = sha512_HMAC.doFinal(data.getBytes("UTF-8"));
        StringBuffer hexSign = new StringBuffer();
        for (int i = 0;i<hash.length;i++) {
            String hexa = Integer.toHexString(0xFF & hash[i]);
            if (hexa.length() == 1) {
                hexSign.append("0");
            }
            hexSign.append(hexa);
        }
        return hexSign.toString();
    }
    public void get_account_balance() throws IOException, InterruptedException, NoSuchAlgorithmException, UnsupportedEncodingException, InvalidKeyException {
        String payload = "\"\\\"\\\"\"";

        PrivateAPI priv = new PrivateAPI(secret_key, api_key);
        String nonce = priv.getNonce();
        String checksum = priv.getChecksum(payload);
        String nonce_checksum = priv.getNonceChecksum(nonce, checksum);
        String signature = priv.getSignature(config.getPrivateAPIEndPoint("ACCOUNT_BALANCE"), nonce_checksum);

        //construct query parameters
        String params = new StringBuilder()
            .append("?nonce=")
            .append(Long.valueOf(nonce))
            .append("&checksum=")
            .append(checksum)
            .append("&payload=")
            .append("")
            .toString();

        //construct request body
        HttpRequest request = HttpRequest.newBuilder()
            .GET()
            .uri(URI.create(config.URL_API_BITWYRE+config.getPrivateAPIEndPoint("ACCOUNT_BALANCE")+params))
            .setHeader("API-Key", api_key)
            .setHeader("API-Sign", signature)
            .build();

        //send request and get response
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
    public void get_account_statement() throws IOException, InterruptedException, NoSuchAlgorithmException, UnsupportedEncodingException, InvalidKeyException {
        String payload = "\"\\\"\\\"\"";

        PrivateAPI priv = new PrivateAPI(secret_key, api_key);
        String nonce = priv.getNonce();
        String checksum = priv.getChecksum(payload);
        String nonce_checksum = priv.getNonceChecksum(nonce, checksum);
        String signature = priv.getSignature(config.getPrivateAPIEndPoint("ACCOUNT_STATEMENT"), nonce_checksum);

        //construct query parameters
        String params = new StringBuilder()
            .append("?nonce=")
            .append(Long.valueOf(nonce))
            .append("&checksum=")
            .append(checksum)
            .append("&payload=")
            .append("")
            .toString();

        //construct request body
        HttpRequest request = HttpRequest.newBuilder()
            .GET()
            .uri(URI.create(config.URL_API_BITWYRE+config.getPrivateAPIEndPoint("ACCOUNT_STATEMENT")+params))
            .setHeader("API-Key", api_key)
            .setHeader("API-Sign", signature)
            .build();

        //send request and get response
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
    public void get_transaction_histories() throws IOException, InterruptedException, NoSuchAlgorithmException, UnsupportedEncodingException, InvalidKeyException {
        String payload = "\"\\\"\\\"\"";

        PrivateAPI priv = new PrivateAPI(secret_key, api_key);
        String nonce = priv.getNonce();
        String checksum = priv.getChecksum(payload);
        String nonce_checksum = priv.getNonceChecksum(nonce, checksum);
        String signature = priv.getSignature(config.getPrivateAPIEndPoint("TRANSACTION_HISTORIES"), nonce_checksum);

        //construct query parameters
        String params = new StringBuilder()
            .append("?nonce=")
            .append(Long.valueOf(nonce))
            .append("&checksum=")
            .append(checksum)
            .append("&payload=")
            .append("")
            .toString();

        //construct request body
        HttpRequest request = HttpRequest.newBuilder()
            .GET()
            .uri(URI.create(config.URL_API_BITWYRE+config.getPrivateAPIEndPoint("TRANSACTION_HISTORIES")+params))
            .setHeader("API-Key", api_key)
            .setHeader("API-Sign", signature)
            .build();

        //send request and get response
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
    public void get_open_orders(String instrument, int from_time, int to_time) throws IOException, InterruptedException, NoSuchAlgorithmException, UnsupportedEncodingException, InvalidKeyException {
        String payload = "\"\\\"{\\\\\\\"instrument\\\\\\\":\\\\\\\"" + instrument + "\\\\\\\",\\\\\\\"from_time\\\\\\\":" + from_time + ",\\\\\\\"to_time\\\\\\\":" + to_time + "}\\\"\"";

        PrivateAPI priv = new PrivateAPI(secret_key, api_key);
        String nonce = priv.getNonce();
        String checksum = priv.getChecksum(payload);
        String nonce_checksum = priv.getNonceChecksum(nonce, checksum);
        String signature = priv.getSignature(config.getPrivateAPIEndPoint("OPEN_ORDERS"), nonce_checksum);
        String payload2 = "{\"instrument\":" + "\"" + instrument + "\"" + ",\"from_time\":" + from_time + ",\"to_time\":" + to_time + "}";
        String encodedPayload = URLEncoder.encode(payload2, "UTF-8");

        //construct query parameters
        String params = new StringBuilder()
            .append("?nonce=")
            .append(Long.valueOf(nonce))
            .append("&checksum=")
            .append(checksum)
            .append("&payload=")
            .append(encodedPayload)
            .toString();

        //construct request body
        HttpRequest request = HttpRequest.newBuilder()
            .GET()
            .uri(URI.create(config.URL_API_BITWYRE+config.getPrivateAPIEndPoint("OPEN_ORDERS")+params))
            .setHeader("API-Key", api_key)
            .setHeader("API-Sign", signature)
            .build();

        //send request and get response
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
    public void get_closed_orders(String instrument, int from_time, int to_time) throws IOException, InterruptedException, NoSuchAlgorithmException, UnsupportedEncodingException, InvalidKeyException {
        String payload = "\"\\\"{\\\\\\\"instrument\\\\\\\":\\\\\\\"" + instrument + "\\\\\\\",\\\\\\\"from_time\\\\\\\":" + from_time + ",\\\\\\\"to_time\\\\\\\":" + to_time + "}\\\"\"";

        PrivateAPI priv = new PrivateAPI(secret_key, api_key);
        String nonce = priv.getNonce();
        String checksum = priv.getChecksum(payload);
        String nonce_checksum = priv.getNonceChecksum(nonce, checksum);
        String signature = priv.getSignature(config.getPrivateAPIEndPoint("CLOSED_ORDERS"), nonce_checksum);
        String payload2 = "{\"instrument\":" + "\"" + instrument + "\"" + ",\"from_time\":" + from_time + ",\"to_time\":" + to_time + "}";
        String encodedPayload = URLEncoder.encode(payload2, "UTF-8");

        //construct query parameters
        String params = new StringBuilder()
            .append("?nonce=")
            .append(Long.valueOf(nonce))
            .append("&checksum=")
            .append(checksum)
            .append("&payload=")
            .append(encodedPayload)
            .toString();

        //construct request body
        HttpRequest request = HttpRequest.newBuilder()
            .GET()
            .uri(URI.create(config.URL_API_BITWYRE+config.getPrivateAPIEndPoint("CLOSED_ORDERS")+params))
            .setHeader("API-Key", api_key)
            .setHeader("API-Sign", signature)
            .build();

        //send request and get response
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
    public void get_order_info(String order_id) throws IOException, InterruptedException, NoSuchAlgorithmException, UnsupportedEncodingException, InvalidKeyException {
        String payload = "\"\\\"\\\"\"";

        PrivateAPI priv = new PrivateAPI(secret_key, api_key);
        String nonce = priv.getNonce();
        String checksum = priv.getChecksum(payload);
        String nonce_checksum = priv.getNonceChecksum(nonce, checksum);
        String signature = priv.getSignature(config.getPrivateAPIEndPoint("ORDER_INFO")+"/"+order_id, nonce_checksum);

        //construct query parameters
        String params = new StringBuilder()
            .append("?nonce=")
            .append(Long.valueOf(nonce))
            .append("&checksum=")
            .append(checksum)
            .append("&payload=")
            .append("")
            .toString();

        //construct request body
        HttpRequest request = HttpRequest.newBuilder()
            .GET()
            .uri(URI.create(config.URL_API_BITWYRE+config.getPrivateAPIEndPoint("ORDER_INFO")+"/"+order_id+params))
            .setHeader("API-Key", api_key)
            .setHeader("API-Sign", signature)
            .build();

        //send request and get response
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
    public void get_trade_history(String instrument, int count, int from_time, int to_time) throws IOException, InterruptedException, NoSuchAlgorithmException, UnsupportedEncodingException, InvalidKeyException {
        String payload = "\"\\\"{\\\\\\\"instrument\\\\\\\":\\\\\\\"" + instrument + "\\\\\\\",\\\\\\\"count\\\\\\\":" + count + ",\\\\\\\"from_time\\\\\\\":" + from_time + ",\\\\\\\"to_time\\\\\\\":" + to_time + "}\\\"\"";

        PrivateAPI priv = new PrivateAPI(secret_key, api_key);
        String nonce = priv.getNonce();
        String checksum = priv.getChecksum(payload);
        String nonce_checksum = priv.getNonceChecksum(nonce, checksum);
        String signature = priv.getSignature(config.getPrivateAPIEndPoint("TRADE_HISTORY"), nonce_checksum);
        String payload2 = "{\"instrument\":" + "\"" + instrument + "\"" + ",\"count\":" + count + ",\"from_time\":" + from_time + ",\"to_time\":" + to_time + "}";
        String encodedPayload = URLEncoder.encode(payload2, "UTF-8");

        //construct query parameters
        String params = new StringBuilder()
            .append("?nonce=")
            .append(Long.valueOf(nonce))
            .append("&checksum=")
            .append(checksum)
            .append("&payload=")
            .append(encodedPayload)
            .toString();

        //construct request body
        HttpRequest request = HttpRequest.newBuilder()
            .GET()
            .uri(URI.create(config.URL_API_BITWYRE+config.getPrivateAPIEndPoint("TRADE_HISTORY")+params))
            .setHeader("API-Key", api_key)
            .setHeader("API-Sign", signature)
            .build();

        //send request and get response
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
    public void opening_new_order(
        String instrument, 
        int side, 
        String price, 
        int ordtype,
        String orderqty
        ) throws IOException, InterruptedException, NoSuchAlgorithmException, UnsupportedEncodingException, InvalidKeyException {
      
        String payload = "\"\\\"{\\\\\\\"instrument\\\\\\\":\\\\\\\"" + instrument + "\\\\\\\",\\\\\\\"side\\\\\\\":" + side + ",\\\\\\\"price\\\\\\\":\\\\\\\"" + price + 
        "\\\\\\\",\\\\\\\"ordtype\\\\\\\":" + ordtype + ",\\\\\\\"orderqty\\\\\\\":\\\\\\\""+ orderqty + "\\\\\\\"}\\\"\"";

        PrivateAPI priv = new PrivateAPI(secret_key, api_key);
        String nonce = priv.getNonce();
        String checksum = priv.getChecksum(payload);
        String nonce_checksum = priv.getNonceChecksum(nonce, checksum);
        String signature = priv.getSignature(config.getPrivateAPIEndPoint("ORDER"), nonce_checksum);
        String payload2 = "{\\\"instrument\\\":" + "\\\"" + instrument + "\\\"" + ",\\\"side\\\":" + side + ",\\\"price\\\":" + "\\\"" + price + "\\\"" + ",\\\"ordtype\\\":" + ordtype +
        ",\\\"orderqty\\\":" + "\\\"" + orderqty + "\\\"" + "}";

        //construct query parameters
        String data = new StringBuilder()
            .append("{")
            .append("\"nonce\":")
            .append(Long.valueOf(nonce))
            .append(",\"checksum\":")
            .append("\"")
            .append(checksum)
            .append("\"")
            .append(",\"payload\":")
            .append("\"")
            .append(payload2)
            .append("\"")
            .append("}")
            .toString();

        //construct request body
        HttpRequest request = HttpRequest.newBuilder()
            .POST(HttpRequest.BodyPublishers.ofString(data))
            .uri(URI.create(config.URL_API_BITWYRE+config.getPrivateAPIEndPoint("ORDER")))
            .setHeader("API-Key", api_key)
            .setHeader("API-Sign", signature)
            .setHeader("Content-Type", "application/json")
            .build();

        //send request and get response
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
    public void cancelling_open_order(String[] order_ids, Integer[] qtys) throws IOException, InterruptedException, NoSuchAlgorithmException, UnsupportedEncodingException, InvalidKeyException {
        //Converting Array to List  
        List<String> list = new ArrayList<String>();  
        for(String id:order_ids){  
            list.add(id);  
        }  
        List<Integer> list2 = new ArrayList<Integer>();
        for (Integer qty:qtys){
            list2.add(qty);
        }
        
        int j;
        String orderids = "";
        for (int i = 0; i < order_ids.length; i++) {
            j = i + 1;
        	orderids = orderids + "\\\\\\\"" +order_ids[i] + "\\\\\\\"";
        	if (j != order_ids.length) {
        		orderids = orderids + ",";
        	}
        }
        int k;
        String temp = "";
        for (int i = 0; i < qtys.length; i++) {
        	k = i + 1;
        	temp = temp + qtys[i];
        	if (k != qtys.length) {
        		temp = temp + ",";
        	}
        } 
        
        String payload = "\"\\\"{\\\\\\\"order_ids\\\\\\\":["+orderids+"],\\\\\\\"qtys\\\\\\\":["+temp+"]}\\\"\"";

        PrivateAPI priv = new PrivateAPI(secret_key, api_key);
        String nonce = priv.getNonce();
        String checksum = priv.getChecksum(payload);
        String nonce_checksum = priv.getNonceChecksum(nonce, checksum);
        String signature = priv.getSignature(config.getPrivateAPIEndPoint("CANCEL_ORDER"), nonce_checksum);
       
        int l;
        String orderids2 = "";
        for (int i = 0; i < order_ids.length; i++) {
            l = i + 1;
        	orderids2 = orderids2 + "\"" +order_ids[i] + "\"";
        	if (l != order_ids.length) {
        		orderids2 = orderids2 + ",";
        	}
        }     
        int m;
        String temp2 = "";
        for (int i = 0; i < qtys.length; i++) {
        	m = i + 1;
        	temp2 = temp2 + qtys[i];
        	if (m != qtys.length) {
        		temp2 = temp2 + ",";
        	}
        }         
        
        String payload2 = "{\"order_ids\":[" + orderids2 + "],\"qtys\":[" + temp2 + "]}";
        String encodedPayload = URLEncoder.encode(payload2, "UTF-8");

        //construct query parameters
        String params = new StringBuilder()
            .append("?nonce=")
            .append(Long.valueOf(nonce))
            .append("&checksum=")
            .append(checksum)
            .append("&payload=")
            .append(encodedPayload)
            .toString();

        //construct request body
        HttpRequest request = HttpRequest.newBuilder()
            .DELETE()
            .uri(URI.create(config.URL_API_BITWYRE+config.getPrivateAPIEndPoint("CANCEL_ORDER")+params))
            .setHeader("API-Key", api_key)
            .setHeader("API-Sign", signature)
            .build();

        //send request and get response
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
    public void cancelling_open_order_per_instrument(String instrument) throws IOException, InterruptedException, NoSuchAlgorithmException, UnsupportedEncodingException, InvalidKeyException {
        String payload = "\"\\\"\\\"\"";

        PrivateAPI priv = new PrivateAPI(secret_key, api_key);
        String nonce = priv.getNonce();
        String checksum = priv.getChecksum(payload);
        String nonce_checksum = priv.getNonceChecksum(nonce, checksum);
        String signature = priv.getSignature(config.getPrivateAPIEndPoint("CANCEL_ORDER")+"/"+"instrument"+"/"+instrument, nonce_checksum);

        //construct query parameters
        String params = new StringBuilder()
            .append("?nonce=")
            .append(Long.valueOf(nonce))
            .append("&checksum=")
            .append(checksum)
            .append("&payload=")
            .append("")
            .toString();

        //construct request body
        HttpRequest request = HttpRequest.newBuilder()
            .DELETE()
            .uri(URI.create(config.URL_API_BITWYRE+config.getPrivateAPIEndPoint("CANCEL_ORDER")+"/"+"instrument"+"/"+instrument+params))
            .setHeader("API-Key", api_key)
            .setHeader("API-Sign", signature)
            .build();

        //send request and get response
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
