#include "GameplayTags/SurvTags.h"

namespace SurvTags
{
	namespace SurvAbilities
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven, "SurvTags.SurvAbilities.ActivateOnGiven", "Tag for auto activating given ability")
		
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, "SurvTags.SurvAbilities.Primary", "Tag for the primary ability")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary, "SurvTags.SurvAbilities.Secondary", "Tag for the secondary ability")
	}
	namespace Events
	{
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "SurvTags.Events.Enemy.HitReact", "Tag for the enemy Hit React")
		}
	}
}