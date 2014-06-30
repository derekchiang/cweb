#pragma once

// cweb_initialize should be called at the beginning of a cweb application, before any other APIs
// are used.  It's OK to call this function multiple times.
extern void cweb_initialize(void);

// cweb_finalize should be called at the  end of a cweb application, after which no APIs should
// be used without calling cweb_initialize() again.
extern void cweb_finalize(void);

