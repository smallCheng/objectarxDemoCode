using System;
using System.Collections.Generic;
using System.Text;
using Autodesk.AutoCAD.Runtime;
using Autodesk.AutoCAD.Customization;
using Autodesk.AutoCAD.ApplicationServices;

namespace RemoveCuiDoubleClick
{
    public class Commands : IExtensionApplication
    {
        // 应用程序初始化
        public void Initialize()
        {
            Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument.Editor.WriteMessage("\nRemoveCuiDoubleClick.dll成功加载了.");
        }

        // 应用程序被卸载、退出
        public void Terminate()
        {

        }

        // 删除直线对象的双击响应
        [CommandMethod("RemoveLineDoubleClick")]
        public void RemoveLineDoubleClick()
        {
            // 获得acad.cui文件的位置并打开它
            string mainCuiFile = (string)Application.GetSystemVariable("MENUNAME");
            mainCuiFile += ".cui";
            CustomizationSection cs = new CustomizationSection(mainCuiFile);

            // 遍历所有的双击处理动作，找到针对直线实体的处理动作
            List<DoubleClickAction> dcsToRemove = new List<DoubleClickAction>();
            foreach (DoubleClickAction dc in cs.MenuGroup.DoubleClickActions)
            {
                if (dc.DxfName.CompareTo("LINE") == 0)
                {
                    dcsToRemove.Add(dc);
                }
            }
            // 删除所有的直线实体双击处理动作
            foreach (DoubleClickAction dc in dcsToRemove)
            {
                cs.MenuGroup.DoubleClickActions.Remove(dc);
            }

            // 保存CUI文件
            if (cs.IsModified)
            {
                cs.Save();
            }
        }
    }
}
