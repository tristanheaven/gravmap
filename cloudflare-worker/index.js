import emscripten from '../src/gravmap.js';

const emscripten_module = new Promise((resolve, reject) => {
	emscripten({
		instantiateWasm(info, receive) {
			const instance = new WebAssembly.Instance(wasm, info);
			receive(instance);
			return instance.exports;
		},
	}).then(module => {
		resolve({
			pngtile: module.cwrap('pngtile', 'number', ['number', 'number', 'number', 'number']),
			tilesize: module.cwrap('tilesize', 'number'),
			tilefree: module.cwrap('tilefree'),
			module: module,
		});
	});
});

async function handleRequest(request) {
	const url = new URL(request.url);

	if (url.pathname == '/gravmap')
		return Response.redirect(request.url + '/');

	if (url.pathname == '/' || url.pathname == '/gravmap/') {
		return new Response(require('html-loader!../web/index.html'),
			{ headers: { 'Content-Type': 'text/html;charset=UTF-8' } }
		);
	}

	if (url.pathname == '/tile.php' || url.pathname == '/gravmap/tile.php') {
		const z = url.searchParams.get('z');
		const x = url.searchParams.get('x');
		const y = url.searchParams.get('y');
		const t = url.searchParams.get('t');

		if (!z || !x || !y || !t)
			return new Response('400', { status: 400 });

		const gravmap = await emscripten_module;
		const pngtile = gravmap.pngtile(z, x, y, t);
		const tilesize = gravmap.tilesize();
		const png = gravmap.module.HEAPU8.slice(pngtile, pngtile + tilesize);
		gravmap.tilefree();

		return new Response(png,
			{ headers: { 'Content-Type': 'image/png' } }
		);
	}

	return new Response('404', { status: 404 });
}

addEventListener('fetch', event => {
	event.respondWith(handleRequest(event.request));
});
