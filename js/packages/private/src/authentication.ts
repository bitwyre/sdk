import axios from "axios";
import crypto from "crypto";

export const currentDateNs = +new Date() * 1000;

export async function getServerTime(baseUrl: string) {
  const uriPath: string = "/public/time";

  return await axios.get(uriPath, {
    baseURL: baseUrl,
  });
}

export interface SignData {
  nonce: number;
  checksum: string;
  signature: string;
}

export async function getNonce(baseUrl: string): Promise<number> {
  const res = await getServerTime(baseUrl);
  return res.data.result.unixtime;
}

export function getChecksum(payload: string): string {
  const temp = JSON.stringify(payload);
  const temp2 = JSON.stringify(temp);
  const temp3 = JSON.stringify(temp2);
  return crypto.createHash("sha256").update(temp3).digest("hex");
}

export function getNonceChecksum(nonce: string, checksum: string): string {
  const noncechecksum = crypto
    .createHash("sha256")
    .update(nonce.concat(checksum))
    .digest("hex");
  return noncechecksum;
}

export async function sign(
  baseUrl: string,
  secretKey: string,
  uriPath: string,
  payload: string
): Promise<SignData> {
  //const nonce: number = await getNonce(baseUrl);
  const nonce: number = Date.now();
  console.log(`Nonce used to compute checksum ${nonce}`);
  const checksum: string = getChecksum(payload);
  const nonceChecksum = getNonceChecksum(nonce.toString(), checksum);
  console.log(`Nonce checksum ${nonceChecksum}`);
  const data = uriPath.concat(nonceChecksum);
  console.log(`data ${data}`);
  const signature = crypto
    .createHmac("sha512", secretKey)
    .update(data)
    .digest("hex");
  console.log(`signature ${signature}`);

  return {
    nonce,
    checksum,
    signature,
  };
}
