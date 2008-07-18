const contractID = "@krickelkrackel/browser/fullscreen-clh;1"
const CID = Components.ID("{DD23C6C4-0884-43f9-8E6A-5DBBE13F7346}")

function ahHandleFullscreen() {}

ahHandleFullscreen.prototype =
{
  QueryInterface: function(iid)
  {
    if (!iid.equals(Components.interfaces.nsICommandLineHandler) &&
        !iid.equals(Components.interfaces.nsISupports))
      throw Components.results.NS_ERROR_NO_INTERFACE;

    return this;
  },

  handle : function ahFullscreen(cmdline)
  {
    if (cmdline.handleFlag("fullscreen", false))
    {
       var ahpref = Components.classes["@mozilla.org/preferences-service;1"]
                   .getService(Components.interfaces.nsIPrefService)
                   .getBranch("extensions.autohide.");

       ahpref.setBoolPref("closedFull", true);
    }
  },

  helpText : "  -fullscreen   Start app in full screen mode.\n"
};

var ahMODFAC =
{
  QueryInterface: function(iid)
  {
    if (!iid.equals(Components.interfaces.nsIModule) &&
        !iid.equals(Components.interfaces.nsIFactory) &&
        !iid.equals(Components.interfaces.nsISupports))
      throw Components.results.NS_ERROR_NO_INTERFACE;

    return this;
  },

  getClassObject: function(compMgr, cid, iid)
  {
    if (!cid.equals(CID))
       throw Components.results.NS_ERROR_NO_INTERFACE;

    return this.QueryInterface(iid);
  },

  registerSelf: function(compMgr, fileSpec, location, type)
  {
    var compR = compMgr.QueryInterface(Components.interfaces.nsIComponentRegistrar);

    compR.registerFactoryLocation(CID, "Fullscreen Cmdline Handler",
                                  contractID, fileSpec, location, type);

    var catM = Components.classes["@mozilla.org/categorymanager;1"]
               .getService(Components.interfaces.nsICategoryManager);

    catM.addCategoryEntry("command-line-handler", "m-fullscreen",
                          contractID, true, true);
  },

  unregisterSelf : function(compMgr, location, type)
  {
    var catM = Components.classes["@mozilla.org/categorymanager;1"]
               .getService(Components.interfaces.nsICategoryManager);

    catM.deleteCategoryEntry("command-line-handler", "m-fullscreen", true);
  },

  canUnload: function(a) {return true;},

  createInstance: function(outer, iid)
  {
    if (outer != null)
       throw Components.results.NS_ERROR_NO_AGGREGATION;

    return new ahHandleFullscreen().QueryInterface(iid);
  },

  lockFactory : function(a) {}
}

function NSGetModule(compMgr, fileSpec)
{
  return ahMODFAC
}