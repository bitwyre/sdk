import crypto from 'crypto';
import axios from 'axios';

export interface SignData {
    nonce: number;
    checksum: string;
    signature: string;
}

export async function getNonce(): Promise<number> {
    const res = await axios.get('https://api.bitwyre.com/public/time');
    return res.data.result.unixtime;
}

export function getChecksum(payload: string): string {
    const temp = JSON.stringify(payload);
    const temp2 = JSON.stringify(temp);
    return crypto.createHash('sha256').update(temp2).digest('hex');
}

export function getNonceChecksum(nonce: string, checksum: string): string {
    return crypto.createHash('sha256').update(nonce.concat(checksum)).digest('hex');
}

export async function sign(secretKey: string, uriPath: string, payload: string): Promise<SignData> {
    const nonce: number = await getNonce();
    
    const checksum: string = getChecksum(payload);
    const nonceChecksum = getNonceChecksum(nonce.toString(), checksum);
    const data = uriPath.concat(nonceChecksum);
    const signature = crypto.createHmac('sha512', secretKey)
        .update(data)
        .digest('hex');

    return {
        nonce: nonce,
        checksum: checksum,
        signature: signature,
    }
}