import { Box, styled, Link } from "@mui/material";
import { StyleConstants } from "../../../styles/StyleConstants";
import { Key, useEffect } from "react";
import { logo } from "../../../data/constants";
import { Margin } from "@mui/icons-material";
interface IExperience {
  span?: string;
  company?: string;
  location?: string;
  twitter?: string;
  linkedIn?: string;
  progress?: any;
}
interface Prop {
  experience: IExperience;
}

const Wrapper = styled(Box)(({ theme }) => ({
  display: "flex",
  alignItems: "center",
  marginBottom: StyleConstants.SPACE_BETWEEN_SECTIONS,
  "& .span": {
    padding: "0 0 6px",
  },
  "& .description-wrapper": {
    paddingBottom: 10,
  },
  "& .description": {
    padding: "0 0 6px 12px",
    display: "flex",
    alignItems: "center",
    "& .bullet": {
      height: 10,
      minWidth: 10,
      backgroundColor: "black",
      borderRadius: "50%",
      marginRight: 10,
    },
  },

  [theme.breakpoints.down("md")]: {
    flexDirection: "column",
    alignItems: "flex-start",
  },
}));
const CompanyWrapper = styled(Box)(({ theme }) => ({
  display: "flex",
  "& .logo": {
    marginRight: 10,
    height: 100,
    width: 100,
    "& img": {
      height: 100,
      width: 100,
    },
  },
  "& .employment-info": {
    fontSize: StyleConstants.SIZE_ITEM_TITLE,
    width: 250,
    marginRight: 10,
    display: "flex",
    justifyContent: "center",
    flexDirection: "column",
    alignItems: "center",
  },
  [theme.breakpoints.down("md")]: {
    "& .employment-info": {
      alignItems: "flex-start",
    },
  },
}));
const DescriptionWrapper = styled(Box)(({ theme }) => ({
  width: 450,
  [theme.breakpoints.down("md")]: {
    paddingTop: 12,
  },
  [theme.breakpoints.down("sm")]: {
    width: 370,
  },
}));
const Experience = ({ experience }: Prop) => {
  const {
    company = "",
    span,
    location,
    progress = [],
  } = experience;

  useEffect(() => {
    window.scrollTo(0, 0);
  }, []);
  const com = "wuttikorn"
  return (
    <Wrapper>
      <CompanyWrapper>
        <div className="logo">
          <img src={logo[com.toLowerCase()]} alt="logo" />
        </div>
        <div className="employment-info">
          <div className="name bold">Wuttikorn communication <br/>and supply</div>
          <div style={{marginLeft: -135}}>{location}</div>
          <div style={{marginLeft: -129}}>{span}</div>
        </div>
      </CompanyWrapper>
      <DescriptionWrapper>
        {progress.map((prog: any) => {
          return (
            <div key={prog.company}>
              <div className="role bold">{prog.role}</div>
              <div className="span">{prog.span}</div>
              <div className="description-wrapper">
                {prog.descriptions.map(
                  (desc: string, ind: Key | null | undefined) => (
                    <div className="description" key={ind}>
                      <div className="bullet" />
                      {desc}
                    </div>
                  )
                )}
              </div>
            </div>
          );
        })}
      </DescriptionWrapper>
    </Wrapper>
  );
};
export default Experience;
