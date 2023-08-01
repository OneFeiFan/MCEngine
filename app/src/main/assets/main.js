Loader.Toast("js加载成功");
//Loader.Toast(Loader.getNewLoader())//.Toast("测试")
/*for (var i = 0; i < 2000; i++) {
  try {
     NativeItem.createItems("test" + i, "apple", 0, true, 1);
  } catch (e) {
     HookEngine.Toast(e);
  }
}*/
/*class Core {
    constructor(p) {}
    static Toast(str) {
        Loader.Toast(str);
    }
};*/
NativeItem.createItem("test", "iron_sword0", 0, true, 1);
NativeItem.createFoodItem("testFood", "apple_golden", 0, true, 1, {"useDuration":1000,"nutrition":10,"saturationLevel":1});
NativeItem.createFoodItem("testFood1", "apple", 0, false, 1, {"useDuration":32,"nutrition":4,"saturationLevel":1});
