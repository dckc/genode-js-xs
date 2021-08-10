/* global trace */
import * as animals from './animals';

export default async function main() {
    let message = "Hello, world - sample";
    trace(message + "\n");

    const dogSays = await animals.bark();
    trace('dog says ', dogSays);
}
