package com.bitwyre.sdk;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
/**
 * For testing only!
 *
 */
public class App 
{
    public static void main( String[] args ) throws IOException, InterruptedException, NoSuchAlgorithmException, UnsupportedEncodingException, InvalidKeyException
    {
    	/*
        PublicAPI.get_server_time();
        PublicAPI.get_asset_pairs("crypto", "spot", "US");
        PublicAPI.get_ticker("btc_idr_spot");
        PublicAPI.get_trades(2, "btc_usd_spot");
        PublicAPI.get_depth("btc_usd_spot", 20);
        PublicAPI.get_assets();
        PublicAPI.get_markets();
        PublicAPI.get_products();
        PublicAPI.get_announcements();
        */
    	
    	PrivateAPI p = new PrivateAPI(System.getenv("SECRET_KEY"), System.getenv("API_KEY"));
    	p.get_account_balance();
    	//p.get_account_statement();
        //p.get_transaction_histories();
        //p.get_open_orders("btc_usdt_spot", 0, 0);
        //p.get_closed_orders("btc_usdt_spot", 0, 0);
        //p.get_trade_history("btc_usdt_spot", 2, 0, 0);
        //p.opening_new_order("btc_usdt_spot", 1, "30000", 2, "0.0125");
        //p.opening_new_order("btc_usdt_spot", 1, "35000", 2, "0.001");
        //p.get_order_info("e7ee03fe-f5bc-47dc-a1a1-5736e5147ca7");
        //p.cancelling_open_order_per_instrument("btc_usdt_spot");
        //p.cancelling_open_order(new String[]{"e7ee03fe-f5bc-47dc-a1a1-5736e5147ca7","c98090d5-3ec0-4e9a-a2e0-2fb904d7580a"},new Integer[]{1,1});	
    }
}
