HookEngine.Toast("js加载成功");
/*for (var i = 0; i < 2000; i++) {
  try {
     NativeItem.createItems("test" + i, "apple", 0, true, 1);
  } catch (e) {
     HookEngine.Toast(e);
  }
}*/
NativeItem.createItem("test", "apple", 0, true, 0);
NativeItem.createFoodItem("testFood", "apple", 0, true, 1, 32, 2,"poor");