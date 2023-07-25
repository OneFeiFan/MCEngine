HookEngine.Toast("js加载成功");
for (var i = 0; i < 10086; i++) {
  try {
     NativeItem.createItems("test" + i, "apple", 0, true, 1);
  } catch (e) {
     HookEngine.Toast(e);
  }
}
//NativeItem.createItems("test", "apple", 0, true, 0);