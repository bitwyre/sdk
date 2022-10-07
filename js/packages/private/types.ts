export interface SignData {
    nonce: number;
    checksum: string;
    signature: string;
}

export type Instruments = "btc_usdt_spot" | "eth_usdt_spot" | "usdt_idr_spot" | "usdc_idr_spot" | "usdc_usd_spot" | "usdt_usd_spot" | "btcusdtx_usdt_200607F1000000";

export const currentDateNs = +new Date * 1000;