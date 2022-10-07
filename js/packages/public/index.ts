import axios from 'axios';

export async function getServerTime(baseUrl: string) {
    const uriPath: string = "/public/time";
    
    return await axios.get(uriPath, {
        baseURL: baseUrl
    });
}

export async function getAssetPairs(baseUrl: string, market: string, product: string, country: string) {
    const uriPath: string = "/public/pairs";
    
    return await axios.get(uriPath, {
        baseURL: baseUrl,
        params: {
            market,
            product,
            country
        }
    });
}

export async function getTicker(baseUrl: string, instrument: string) {
    const uriPath: string = "/public/ticker";
    
    return await axios.get(uriPath, {
        baseURL: baseUrl,
        params: {
            instrument
        }
    });
}

export async function getTrades(baseUrl: string, tradeNum: number, instrument: string) {
    const uriPath: string = "/public/trades";
    
    return await axios.get(uriPath, {
        baseURL: baseUrl,
        params: {
            instrument,
            trade_num: tradeNum
        }
    });
}

export async function getDepth(baseUrl: string, instrument: string, depthNum: number) {
    const uriPath: string = "/public/depth";
    
    return await axios.get(uriPath, {
        baseURL: baseUrl,
        params: {
            instrument,
            depth_num: depthNum
        }
    });
}

export async function getAssets(baseUrl: string) {
    const uriPath: string = "/public/assets";
    
    return await axios.get(uriPath, {
        baseURL: baseUrl
    });
}

export async function getMarkets(baseUrl: string) {
    const uriPath: string = "/public/markets";
    
    return await axios.get(uriPath, {
        baseURL: baseUrl
    });
}

export async function getProducts(baseUrl: string) {
    const uriPath: string = "/public/products";
    
    return await axios.get(uriPath, {
        baseURL: baseUrl
    });
}

export async function getAnnouncements(baseUrl: string) {
    const uriPath: string = "/public/announcements";
    
    return await axios.get(uriPath, {
        baseURL: baseUrl
    });
}
