#include "GameplayTags/SurvTags.h"

namespace SurvTags
{
	namespace SurvAbilities
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven, "SurvTags.SurvAbilities.ActivateOnGiven", "Tag for auto activating given ability")
		
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, "SurvTags.SurvAbilities.Primary", "Tag for the primary ability")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary, "SurvTags.SurvAbilities.Secondary", "Tag for the secondary ability")

		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attack, "SurvTags.SurvAbilities.Enemy.Attack", "Tag for the enemy attack ability")
		}
	}
	namespace Events
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(KillScored, "SurvTags.Events.KillScored", "Tag for an enemy is KillScored Event")
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "SurvTags.Events.Enemy.HitReact", "Tag for the enemy Hit React")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(EndAttack, "SurvTags.Events.Enemy.EndAttack", "Tag for the enemy ending the attack")
		}
	}
}