type stats;

[@bs.module "fs"] external statSync: string => Js.t({..}) = "";

[@bs.module "crypto"] external createHash: string => Js.t({..}) = "";

[@bs.module "fs"] external renameSync: (string, string) => unit = "";

[@bs.module "fs"] external mkdirSync: string => unit = "";

[@bs.module "fs"]
external appendFileSync: (string, string, string) => unit = "";