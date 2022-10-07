import { getAccountBalance } from '../src';
import * as dotenv from 'dotenv';

dotenv.config({ path: `${__dirname}/../.env` });

async function main() {
  const res = await getAccountBalance(
    process.env.BASE_URL ?? '',
    process.env.API_KEY ?? '',
    process.env.SECRET_KEY ?? '',
  );
  return res.data;
}

main()
  .then(console.log)
  .catch((e) => console.log(e.response.data));
