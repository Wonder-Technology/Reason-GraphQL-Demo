module ActiveUserType = {
  type activeUserType =
    | Success
    | ParamError
    | DBSqlError
    | GithubRepoError
    | AlreadyActive
    | CodeError
    | UserNameNotExist;

  external convertSelfToInt: activeUserType => int = "%identity";

  external convertIntToSelf: int => activeUserType = "%identity";
};

module CheckUserLoginType = {
  type checkUserLoginType =
    | Success
    | ParamError
    | InValidParam
    | DBSqlError
    | UserNotActive
    | PasswordError
    | UserNameNotExist;

  external convertSelfToInt: checkUserLoginType => int = "%identity";
};

module RegisterUserType = {
  type registerUserType =
    | Success
    | ParamError
    | DBSqlError
    | InValidParam
    | SendEmailError;

  external convertSelfToInt: registerUserType => int = "%identity";

  external convertIntToSelf: int => registerUserType = "%identity";
};

module SendEmailToRetrievePasswordType = {
  type sendEmailType =
    | Success
    | Fail
    | ParamError
    | DBSqlError
    | UserNameNotExist;

  external convertSelfToInt: sendEmailType => int = "%identity";
};

module UploadUserProfileType = {
  type uploadUserProfileType =
    | Success
    | InValidParam
    | ParamError
    | DBSqlError
    | ChunkCountError
    | UserInfoNotExist;

  external convertSelfToInt: uploadUserProfileType => int = "%identity";

  external convertIntToSelf: int => uploadUserProfileType = "%identity";
};

module UploadFileChunkType = {
  type uploadFileChunkType =
    | Success
    | OperateFileError
    | ParamError;

  external convertSelfToInt: uploadFileChunkType => int = "%identity";

  external convertIntToSelf: int => uploadFileChunkType = "%identity";
};