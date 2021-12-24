/* global trace */
import * as animals from './animals';
import { fun } from './FFI';

export default async function main(io) {
    let message = "Hello, world - sample";
    trace(message + "\n");

    const dogSays = await animals.bark();
    trace('dog says ', dogSays, '\n');

    trace('genode logging:\n');
    fun("js to genode");

    trace(JSON.stringify({ io, ty: typeof io.sandbox.applyConfig }));
    const { sandbox } = io;
    sandbox.applyConfig(`
    <config>
    <parent-provides>
    <service name="ROM" />
    <service name="LOG" />
    <service name="RM" />
    <service name="CPU" />
    <service name="PD" />
    <service name="Timer" />
    <service name="Nic" />
    </parent-provides>

    <default-route>
        <any-service>
            <parent />
            <any-child />
        </any-service>
    </default-route>

    <default caps="500" />

    <start name="xxx">
        <resource name="RAM" quantum="200M" />
    </start>
    </config>
    `);
}
