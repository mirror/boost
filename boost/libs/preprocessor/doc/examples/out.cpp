

extern "C" {

 void _assert(const char*, const char*, unsigned);

}

int main(void) {
	int i = 0;
	do { int duffs_device_initial_cnt = (0); if (duffs_device_initial_cnt > 0) { int duffs_device_running_cnt = (duffs_device_initial_cnt + (16 - 1)) / 16; switch (duffs_device_initial_cnt % 16) { do { case (0 ? 16 - 0 : 0): { ++i; }; case (1 ? 16 - 1 : 0): { ++i; }; case (2 ? 16 - 2 : 0): { ++i; }; case (3 ? 16 - 3 : 0): { ++i; }; case (4 ? 16 - 4 : 0): { ++i; }; case (5 ? 16 - 5 : 0): { ++i; }; case (6 ? 16 - 6 : 0): { ++i; }; case (7 ? 16 - 7 : 0): { ++i; }; case (8 ? 16 - 8 : 0): { ++i; }; case (9 ? 16 - 9 : 0): { ++i; }; case (10 ? 16 - 10 : 0): { ++i; }; case (11 ? 16 - 11 : 0): { ++i; }; case (12 ? 16 - 12 : 0): { ++i; }; case (13 ? 16 - 13 : 0): { ++i; }; case (14 ? 16 - 14 : 0): { ++i; }; case (15 ? 16 - 15 : 0): { ++i; }; } while (--duffs_device_running_cnt); } } } while (0);
	(void)( (i == 0) || (_assert("i == 0", "duffs_device.c", 58), 0) );
	do { int duffs_device_initial_cnt = (1000); if (duffs_device_initial_cnt > 0) { int duffs_device_running_cnt = (duffs_device_initial_cnt + (16 - 1)) / 16; switch (duffs_device_initial_cnt % 16) { do { case (0 ? 16 - 0 : 0): { ++i; }; case (1 ? 16 - 1 : 0): { ++i; }; case (2 ? 16 - 2 : 0): { ++i; }; case (3 ? 16 - 3 : 0): { ++i; }; case (4 ? 16 - 4 : 0): { ++i; }; case (5 ? 16 - 5 : 0): { ++i; }; case (6 ? 16 - 6 : 0): { ++i; }; case (7 ? 16 - 7 : 0): { ++i; }; case (8 ? 16 - 8 : 0): { ++i; }; case (9 ? 16 - 9 : 0): { ++i; }; case (10 ? 16 - 10 : 0): { ++i; }; case (11 ? 16 - 11 : 0): { ++i; }; case (12 ? 16 - 12 : 0): { ++i; }; case (13 ? 16 - 13 : 0): { ++i; }; case (14 ? 16 - 14 : 0): { ++i; }; case (15 ? 16 - 15 : 0): { ++i; }; } while (--duffs_device_running_cnt); } } } while (0);
	(void)( (i == 1000) || (_assert("i == N", "duffs_device.c", 60), 0) );
	return 0;
}
