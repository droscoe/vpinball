#pragma once

#define MINI_CASE_SENSITIVE
#include "mINI/ini.h"

// This class holds the settings registry.
// A setting registry can have a parent, in which case, missing settings will be looked for in the parent.
// This is used to allow overriding part of the settings for a specific table while still using the base application value for others.
// When saving value, an 'override mode' can be used where the value will be saved only if it not the same as the one in the parent.
class Settings final
{
public:
   Settings(const Settings* parent = nullptr);

   void SetParent(const Settings *parent) { m_parent = parent; }

   void SetIniPath(const string &path) { m_iniPath = path; }
   bool LoadFromFile(const string &path, const bool createDefault);
   void SaveToFile(const string &path);
   void Save();

   void CopyOverrides(const Settings &settings);

   // Save only actually save the settings if they have been modified. If you want to force a save (for example if filepath has changed), you need to expcitely set the modified flag
   bool IsModified() const { return m_modified; }
   void SetModified(const bool modified) { m_modified = modified; }

   enum Section
   {
      Controller,

      // UI and Player stuff
      Editor,
      Player,
      PlayerVR,
      RecentDir,
      Version,
      CVEdit,
      TableOverride,

      // Optional user defaults for each element
      DefaultPropsBumper,
      DefaultPropsDecal,
      DefaultPropsEMReel,
      DefaultPropsFlasher,
      DefaultPropsFlipper,
      DefaultPropsGate,
      DefaultPropsHitTarget,
      DefaultPropsKicker,
      DefaultPropsLight,
      DefaultPropsLightSequence,
      DefaultPropsPlunger,
      DefaultPropsPrimitive,
      DefaultPropsRamp,
      DefaultPropsRubber,
      DefaultPropsSpinner,
      DefaultPropsWall,
      DefaultPropsTarget,
      DefaultPropsTextBox,
      DefaultPropsTimer,
      DefaultPropsTrigger,
      DefaultCamera,

      Count
   };

   static Section GetSection(const string& szName);

   bool HasValue(const Section section, const string &key, const bool searchParent = false) const;

   bool LoadValue(const Section section, const string &key, string &buffer) const;
   bool LoadValue(const Section section, const string &key, void *const szbuffer, const DWORD size) const;
   bool LoadValue(const Section section, const string &key, float &pfloat) const;
   bool LoadValue(const Section section, const string &key, int &pint) const;
   bool LoadValue(const Section section, const string &key, unsigned int &pint) const;

   float LoadValueWithDefault(const Section section, const string &key, const float def) const;
   int LoadValueWithDefault(const Section section, const string &key, const int def) const;
   bool LoadValueWithDefault(const Section section, const string &key, const bool def) const;
   string LoadValueWithDefault(const Section section, const string &key, const string &def) const;

   bool SaveValue(const Section section, const string &key, const char *val, const bool overrideMode = false);
   bool SaveValue(const Section section, const string &key, const string &val, const bool overrideMode = false);
   bool SaveValue(const Section section, const string &key, const float val, const bool overrideMode = false);
   bool SaveValue(const Section section, const string &key, const int val, const bool overrideMode = false);
   bool SaveValue(const Section section, const string &key, const bool val, const bool overrideMode = false);

   bool DeleteValue(const Section section, const string &key, const bool& deleteFromParent = false);
   bool DeleteSubKey(const Section section, const bool &deleteFromParent = false);

private:
   enum DataType
   {
      DT_SZ, // char*, 0 terminated
      DT_DWORD,
      DT_ERROR
   };

   bool LoadValue(const Section section, const string &key, DataType &type, void *pvalue, DWORD size) const;
   bool SaveValue(const Section section, const string &key, const DataType type, const void *pvalue, const DWORD size, const bool overrideMode);

   bool m_modified = false;
   string m_iniPath;
   mINI::INIStructure m_ini;
   const Settings *m_parent;
};
