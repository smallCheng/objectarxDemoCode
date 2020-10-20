using System;
using System.Collections.Generic;
using System.Text;
using Autodesk.AutoCAD.Runtime;
using Autodesk.AutoCAD.DatabaseServices;
using Zfgk.TriangleEntityDB;
using Autodesk.AutoCAD.EditorInput;
using Autodesk.AutoCAD.Geometry;

namespace CSharpUseTriangleEntity
{
    public class Commands
    {
        [CommandMethod("AddTriangle")]
        public void AddTriangle()
        {
            Database db = HostApplicationServices.WorkingDatabase;
            using (Transaction trans = db.TransactionManager.StartTransaction())
            {
                BlockTable bt = (BlockTable)trans.GetObject(db.BlockTableId, OpenMode.ForRead);
                BlockTableRecord btr = (BlockTableRecord)trans.GetObject(db.CurrentSpaceId, OpenMode.ForWrite);

                // 提示用户拾取三点
                Point3d pt1 = new Point3d();
                Point3d pt2 = new Point3d();
                Point3d pt3 = new Point3d();
                if (GetPoint("\n输入起点:", out pt1) && 
                    GetPoint("\n输入终点:", pt1, out pt2) && 
                    GetPoint("\n输入终点:", pt2, out pt3))
                {
                    MgTriangle triangle = new MgTriangle(pt1, pt2, pt3);
                    double area = triangle.Area;
                    btr.AppendEntity(triangle);
                    trans.AddNewlyCreatedDBObject(triangle, true);

                    Editor ed = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument.Editor;
                    ed.WriteMessage("\n三角形的面积:{0}", area);

                    trans.Commit();
                }
            }
        }

        [CommandMethod("test")]
        public void test()
        {
            Database db = HostApplicationServices.WorkingDatabase;
            Editor ed = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument.Editor;

            PromptEntityOptions opt = new PromptEntityOptions("\n请选择对象");
            PromptEntityResult res = ed.GetEntity(opt);

            using (Transaction trans = db.TransactionManager.StartTransaction())
            {
                Entity ent = trans.GetObject(res.ObjectId, OpenMode.ForWrite) as Entity;
                if (ent is MgTriangle)
                {
                    MgTriangle triangle = ent as MgTriangle;
                    triangle.ColorIndex = 1;

                    trans.Commit();
                }
            }
        }

        // 提示用户拾取点
        public bool GetPoint(string prompt, out Point3d pt)
        {
            Editor ed = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument.Editor;
            PromptPointResult ppr = ed.GetPoint(prompt);
            if (ppr.Status == PromptStatus.OK)
            {
                pt = ppr.Value;

                // 变换到世界坐标系
                Matrix3d mat = ed.CurrentUserCoordinateSystem;
                pt.TransformBy(mat);

                return true;
            }
            else
            {
                pt = new Point3d();
                return false;
            }
        }

        public bool GetPoint(string prompt, Point3d basePoint, out Point3d pt)
        {
            Editor ed = Autodesk.AutoCAD.ApplicationServices.Application.DocumentManager.MdiActiveDocument.Editor;
            PromptPointOptions ppo = new PromptPointOptions(prompt);
            ppo.BasePoint = basePoint;
            ppo.UseBasePoint = true;
            PromptPointResult ppr = ed.GetPoint(ppo);
            if (ppr.Status == PromptStatus.OK)
            {
                pt = ppr.Value;

                // 变换到世界坐标系
                Matrix3d mat = ed.CurrentUserCoordinateSystem;
                pt.TransformBy(mat);

                return true;
            }
            else
            {
                pt = new Point3d();
                return false;
            }
        }
    }
}
