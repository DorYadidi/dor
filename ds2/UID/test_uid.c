#include <time.h>
#include <unistd.h>
#include "uid.h"
#include "test.h"


TestResult TestUID();


int main()
{
	RUN_TEST(TestUID);

	return (0);
}

TestResult TestUID()
{
	unique_id_t uid1;
	unique_id_t uid2;
	unique_id_t bad_id;

	/*test Create*/
	uid1 = UIDCreate();
	REQUIRE(0 == uid1.sequence);
	sleep(1);
	uid2 = UIDCreate();
	REQUIRE(1 == uid2.sequence);
	REQUIRE(uid1.time < uid2.time);

	/*Is Same*/
	REQUIRE(UIDIsSame(uid1, uid2) == FALSE);
	REQUIRE(UIDIsBad(uid1) == FALSE);

	/*Get Bad*/
	bad_id = UIDGetBad();
	REQUIRE(UIDIsBad(bad_id) == TRUE);



	return (TEST_PASS);
}
