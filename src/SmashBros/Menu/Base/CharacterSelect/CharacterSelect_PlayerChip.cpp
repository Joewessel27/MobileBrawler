
#include "CharacterSelect_PlayerChip.h"
#include "CharacterSelect_CharacterIcon.h"
#include "CharacterSelectScreen.h"

namespace SmashBros
{
	namespace Menu
	{
		namespace CharacterSelect
		{
			PlayerChip::PlayerChip(unsigned int pNum, CharacterSelectScreen*screen, float x, float y, AssetManager*assetManager) : SpriteActor(x,y)
			{
				playerNum = pNum;
				charSelectScreen = screen;
				addAnimation("default", new Animation(1, assetManager, (String)"characterselect/chip_p" + playerNum + ".png"));
				addAnimation("cpu", new Animation(1, assetManager, "characterselect/chip_cpu.png"));
				changeAnimation("default", Animation::FORWARD);
				dragging = false;
				dragTouchID = 0;
				dragOffset.x = 0;
				dragOffset.y = 0;
			}
			
			PlayerChip::~PlayerChip()
			{
				//
			}
			
			void PlayerChip::onMousePress(ApplicationData appData, unsigned int touchID)
			{
				if(!dragging)
				{
					bool touch_alreadyBeingUsed = false;
					for(unsigned int i=0; i<charSelectScreen->chips.size(); i++)
					{
						PlayerChip*chip = charSelectScreen->chips.get(i);
						if(chip != this)
						{
							if(chip->dragging && chip->dragTouchID == touchID)
							{
								touch_alreadyBeingUsed = true;
							}
						}
					}
					if(!touch_alreadyBeingUsed)
					{
						grabChip(appData, touchID);
					}
				}
			}
			
			void PlayerChip::update(ApplicationData appData)
			{
				//updating dragging
				if(dragging)
				{
					if(Multitouch::isEnabled())
					{
						if(Multitouch::isTouchActive(appData.getWindow(), dragTouchID))
						{
							Vector2f touchpos = appData.getTransform().getInverse().transform(Multitouch::getPosition(appData.getWindow(), dragTouchID));
							x = touchpos.x;
							y = touchpos.y;
						}
						else
						{
							releaseChip();
						}
					}
					else
					{
						if(Mouse::isButtonPressed(appData.getWindow(), dragTouchID, Mouse::BUTTON_LEFT))
						{
							Vector2f mousepos = appData.getTransform().getInverse().transform(Mouse::getPosition(appData.getWindow(), dragTouchID));
							x = mousepos.x;
							y = mousepos.y;
						}
						else
						{
							releaseChip();
						}
					}
				}
				SpriteActor::update(appData);
				
				//check if overlapping with any character icons;
				CharacterInfo* overlap_charInfo = nullptr;
				float overlap_area = 0;
				ArrayList<CharacterIcon*>& icons = charSelectScreen->icons;
				RectangleF frame = getFrame();
				for(unsigned int i=0; i<icons.size(); i++)
				{
					CharacterIcon* icon = icons.get(i);
					RectangleF iconFrame = icon->getFrame();
					if(frame.intersects(iconFrame))
					{
						RectangleF overlap = frame.getIntersect(iconFrame);
						float area = overlap.getArea();
						if(area > overlap_area)
						{
							overlap_charInfo = icon->getCharacterInfo();
							overlap_area = area;
						}
					}
				}
				CharacterInfo* oldInfo = charSelectScreen->rules->getPlayerInfo(playerNum).getCharacterInfo();
				charSelectScreen->rules->getPlayerInfo(playerNum).setCharacterInfo(overlap_charInfo);
				if(oldInfo != overlap_charInfo)
				{
					//event: whenPlayerCharacterChanges
					charSelectScreen->whenPlayerCharacterChanges(playerNum, overlap_charInfo);
				}
			}
			
			void PlayerChip::grabChip(const ApplicationData&appData, unsigned int touchID)
			{
				dragging = true;
				dragTouchID = touchID;
				Transform mouseTransform = appData.getTransform().getInverse();
				if(Multitouch::isEnabled())
				{
					dragOffset = mouseTransform.transform(Multitouch::getPosition(appData.getWindow(), touchID)) - Vector2f(x,y);
				}
				else
				{
					dragOffset = mouseTransform.transform(Mouse::getPosition(appData.getWindow(), touchID)) - Vector2f(x,y);
				}
				unsigned int index = charSelectScreen->chips.indexOf(this);
				charSelectScreen->chips.remove(index);
				charSelectScreen->chips.add(0,this);
			}
			
			void PlayerChip::releaseChip()
			{
				if(dragging)
				{
					dragging = false;
					dragTouchID = 0;
					//event: whenPlayerChipReleased
				}
			}
		}
	}
}
