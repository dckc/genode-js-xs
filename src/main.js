/* global trace */
import * as animals from './animals';
import { fun } from './FFI';

export default async function main() {
    let message = "Hello, world - sample";
    trace(message + "\n");

    const dogSays = await animals.bark();
    trace('dog says ', dogSays, '\n');

    trace('genode logging:\n');
    fun("js to genode");
}
