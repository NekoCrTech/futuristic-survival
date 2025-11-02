#include "GameplayTags/SurvTags.h"

namespace SurvTags
{
	namespace SetByCaller
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Projectile, "SurvTags.SetByCaller.Projectile", "Tag for Projectile")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Melee, "SurvTags.SetByCaller.Melee", "Tag for Melee")
	}
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
		namespace Player
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "SurvTags.Events.Player.HitReact", "Tag for the player Hit React")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Death, "SurvTags.Events.Player.Death", "Tag for the player death")
		}
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "SurvTags.Events.Enemy.HitReact", "Tag for the enemy Hit React")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(EndAttack, "SurvTags.Events.Enemy.EndAttack", "Tag for the enemy ending the attack")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(MeleeTraceHit, "SurvTags.Events.Enemy.MeleeTraceHit", "Tag for the enemy melee trace hit")
		}
	}
}