const CopyPlugin = require('copy-webpack-plugin');

module.exports = {
	target: 'webworker',
	context: __dirname,
	entry: './index.js',
	plugins: [
		new CopyPlugin([
			{ from: '../src/gravmap.wasm', to: './worker/gravmap.wasm' }
		])
	]
};
