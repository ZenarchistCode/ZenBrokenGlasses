modded class MissionGameplay
{
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice); 

		if (!GetGame())
			return;

		//! BROKEN GLASSES
		UpdateZenBrokenGlasses();
	}

	//! BROKEN GLASSES
	void UpdateZenBrokenGlasses()
	{
#ifdef EDITOR
		return;
#endif

		ZenBrokenGlassesWidget brokenGlassesWidget = ZenBrokenGlassesWidget.GetZenBrokenGlassesWidget();
		if (!brokenGlassesWidget)
			return;

		// No HUD - stop here.
		if (!m_Hud)
		{
			brokenGlassesWidget.HideFX();
			return;
		}

		if (!GetGame().GetPlayer() || !GetGame().GetPlayer().IsAlive() || GetGame().GetPlayer().IsUnconscious())
		{
			brokenGlassesWidget.HideFX();
			return;
		}

		if (GetGame().GetUIManager().GetMenu() != NULL && !GetGame().GetUIManager().FindMenu(MENU_INVENTORY) && !GetGame().GetUIManager().FindMenu(MENU_CHAT_INPUT))
		{
			brokenGlassesWidget.HideFX();
			return;
		}

		bool notNull = brokenGlassesWidget != NULL;
		brokenGlassesWidget.ShowFX(GetBrokenGlassesLevel());
	}

	// -1 means no glasses or no damage, >= 1 means damaged
	int GetBrokenGlassesLevel()
	{
		int damageLevel = -1;

		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (!player)
			return damageLevel;

		string type;
		
		// Check visor
		if (player.FindAttachmentBySlotName("Headgear"))
		{
			ItemBase helmet = ItemBase.Cast(player.FindAttachmentBySlotName("Headgear"));
			if (helmet)
			{
				type = helmet.GetType();
				type.ToLower();

				// Check moto helm
				if (type.Contains("motohelmet"))
				{
					damageLevel = Math.Max(damageLevel, helmet.GetHealthLevel());
				}
				else 
				{
					// Check Gorka visor
					ItemBase visor = ItemBase.Cast(player.FindAttachmentBySlotName("Headgear").FindAttachmentBySlotName("Glass"));
					if (visor)
					{
						// If visor is damaged return its damage level first
						damageLevel = Math.Max(damageLevel, visor.GetHealthLevel());
					}
				}
			}
		}

		// Check gas mask
		if (player.FindAttachmentBySlotName("Mask"))
		{
			Clothing mask = Clothing.Cast(player.FindAttachmentBySlotName("Mask"));
			if (mask && mask.IsGasMask())
			{
				damageLevel = Math.Max(damageLevel, mask.GetHealthLevel());
			}
		}

		// Check glasses
		Clothing glasses = Clothing.Cast(player.FindAttachmentBySlotName("Eyewear"));
		if (!glasses)
			return damageLevel;

		// Final check for modded glasses without PPE effect
		type = glasses.GetType();
		type.ToLower();
		if (glasses.GetGlassesEffectID() == -1 && !type.Contains("glasses"))
			return damageLevel;

		// Return whatever is higher - our glasses damage or our visor damage
		return Math.Max(glasses.GetHealthLevel(), damageLevel);
	}
}
