/* global trace */
export default async function main() {
    let message = "Hello, world - sample";
    Promise.resolve(null).then(() => {
        trace('promise callback works.')
    })
    trace(message + "\n");
}
