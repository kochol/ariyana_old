#define CR_HOST // required in the host only and before including cr.h
#include "../../deps/cr/cr.h"

const char *plugin = BUILD_DIR CR_PLUGIN("shivaeditorDebug");

int main(int argc, char *argv[]) {
	cr_plugin ctx;
	// the host application should initalize a plugin with a context, a plugin
	// filename without extension and the full path to the plugin
	cr_plugin_load(ctx, plugin);

	// call the plugin update function with the plugin context to execute it
	// at any frequency matters to you
	while (cr_plugin_update(ctx)) {
		
	}

	// at the end do not forget to cleanup the plugin context, as it needs to
	// allocate some memory to track internal and plugin states
	cr_plugin_close(ctx);
	return 0;
}
